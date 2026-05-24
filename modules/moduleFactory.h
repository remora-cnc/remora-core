#ifndef MODULE_FACTORY_H
#define MODULE_FACTORY_H

#include <memory>
#include <map>
#include <functional>
#include <string>
#include <ArduinoJson.h>

#include "module.h"

class Remora;

class ModuleFactory
{
public:
    using CreatorFn = std::function<std::shared_ptr<Module>(const JsonVariant&, Remora*)>;

    static ModuleFactory* getInstance()
    {
        static ModuleFactory instance;
        return &instance;
    }

    bool registerModule(const char* typeName, CreatorFn creator)
    {
        auto& reg = getRegistry();
        if (reg.count(typeName)) {
            printf("ModuleFactory: WARNING — duplicate registration '%s'\n", typeName);
            return false;
        }
        reg.emplace(typeName, std::move(creator));
        return true;
    }

    std::shared_ptr<Module> createModule(const char* thread,
                                         const char* typeName,
                                         const JsonVariant& config,
                                         Remora* remora)
    {
        auto& reg = getRegistry();
        auto  it  = reg.find(typeName);
        if (it == reg.end()) {
            printf("ModuleFactory: unknown module type '%s'\n", typeName);
            return nullptr;
        }
        return it->second(config, remora);
    }

    template<typename T>
    struct Registrar
    {
        explicit Registrar(const char* typeName)
        {
            ModuleFactory::getInstance()->registerModule(
                typeName,
                [](const JsonVariant& config, Remora* remora) -> std::shared_ptr<Module>
                {
                    return T::create(config, remora);
                });
        }
    };

    ModuleFactory(const ModuleFactory&)            = delete;
    ModuleFactory& operator=(const ModuleFactory&) = delete;

private:
    ModuleFactory() = default;

    static std::map<std::string, CreatorFn>& getRegistry()
    {
        static std::map<std::string, CreatorFn> registry;
        return registry;
    }
};

#endif // MODULE_FACTORY_H