#include <ac\es.h>
#include <list>

#include <Pulse.h>

/**
	NodeComponent
	The node handles all natural/environmental features of a node. Mainly it's energy consumption, and later a reference to a HubComponent.
**/

#pragma once
#include "OgreEntity.h"
namespace np
{
	
	class NodeComponent : public ac::es::Component
	{
		AC_ES_COMPONENT(NodeComponent)
	public:

		double energyThreshold;
		double currentEnergy;

		double temperature;

		double heatDissipation;
		double heatCapacity;

		bool isSelected;

		Ogre::Entity* reactor;

		NodeComponent( double energyThreshold);
		~NodeComponent(void);
		
	};
}