#ifndef DEBUG_H
#define DEBUG_H

#include <cstdint>
#include <string>

#include "../../modules/module.h"
#include "../../../remora-hal/pin/pin.h"

// Forward declaration — avoids pulling all of remora.h into the module header.
class Remora;

class Debug : public Module
{

	private:

		bool 		bState;

		Pin*        debugPin;	// class object members - Pin objects

	public:

		Debug(std::string, bool);

		virtual void update(void);
		virtual void slowUpdate(void);
};

#endif
