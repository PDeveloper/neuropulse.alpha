#include "Event.h"
#include <EventType.h>

np::Event::Event(np::EventType* type)
{
	this->type = type;
}


np::Event::~Event(void)
{
}
