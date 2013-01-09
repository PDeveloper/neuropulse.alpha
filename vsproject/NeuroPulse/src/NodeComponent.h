#include <ac\es.h>
#include <list>

#include <Pulse.h>

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

		std::list<np::Pulse*> outPulseBuffer;
		std::list<np::Pulse*> inPulseBuffer;

		NodeComponent( double energyThreshold);
		~NodeComponent(void);
		
	};
}