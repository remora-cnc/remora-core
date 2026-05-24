#ifndef RESETPIN_H
#define RESETPIN_H

#include <string>
#include <memory>
#include "../../modules/module.h"
#include "../../modules/moduleFactory.h"
#include "../../../remora-hal/pin/pin.h"

// Forward declaration — avoids pulling all of remora.h into the module header.
class Remora;

// Global PRUreset variable (declared in extern.h or another source file)
extern volatile bool PRUreset;

class ResetPin : public Module {
private:
    volatile bool* ptrReset;  // Pointer to PRUreset
    std::string portAndPin;   // Pin identifier
    Pin* pin;                 // Pin object

public:
    ResetPin(volatile bool* ptrReset, const std::string& portAndPin);
    static std::shared_ptr<Module> create(const JsonObject& config, Remora* instance);

    void update() override;
    void slowUpdate() override;
};

#endif // RESETPIN_H
