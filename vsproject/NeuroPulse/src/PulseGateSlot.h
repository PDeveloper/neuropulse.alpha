#include <PulseGateComponent.h>
#include <ac/es.h>

#pragma once
namespace np
{
	class PulseGateSlot
	{
	public:

		ac::es::EntityPtr pulseGate;

		double getPosition() const
		{
			return pulseGate->getComponent<np::PulseGateComponent>()->position;
		}

		PulseGateSlot(ac::es::EntityPtr pulseGate)
		{
			this->pulseGate = pulseGate;
		}

		bool operator < (const np::PulseGateSlot& slot) const
		{
			return ( getPosition() < slot.getPosition());
		}
	};
}

