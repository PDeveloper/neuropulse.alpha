#include <Event2.h>

#include <ac/es.h>

#pragma once
namespace np
{
	class PulseEvent : public np::Event
	{
	public:

		ac::es::EntityPtr target1;
		ac::es::EntityPtr target2;

		PulseEvent( np::EventType* type, ac::es::EntityPtr target1, ac::es::EntityPtr target2) :
			np::Event( type)
		{
			this->target1 = target1;
			this->target2 = target2;
		}

		~PulseEvent(void)
		{
		}
	};
}

