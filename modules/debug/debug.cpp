#include "debug.h"
#include "../../remora.h"

// Debug does not have a registrar as it is not intended to be created from the config file, but rather used for one-off debugging purposes by creating an instance in the thread and calling update() directly.

Debug::Debug(std::string portAndPin, bool bstate) :
    bState(bstate)
{
	this->debugPin = new Pin(portAndPin, OUTPUT);
}

void Debug::update(void)
{
	this->debugPin->set(bState);
}

void Debug::slowUpdate(void)
{
	return;
}
