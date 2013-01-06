#include <ac\es.h>
#include <list>

#include <PulseComponent.h>

/**
	NodeComponent
	The node handles all natural/environmental features of a node. Mainly it's energy consumption, and later a reference to a HubComponent.
**/

#pragma once
namespace np
{
	class NodeComponent : public ac::es::Component
	{
		AC_ES_COMPONENT(NodeComponent)
	public:

		double energyThreshold;
		double currentEnergy;

		std::list<np::PulseComponent> outPulseBuffer;
		std::list<np::PulseComponent> inPulseBuffer;

		NodeComponent( double energyThreshold)
		{
			this->energyThreshold = energyThreshold;
			currentEnergy = 0.0;
		}

		~NodeComponent(void)
		{

		}
	};
}