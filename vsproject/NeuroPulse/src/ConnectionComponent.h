#include <ac\es.h>
#include <vector>

#include <NodeComponent.h>
#include <PulseComponent.h>

/**
	ConnectionComponent
	This component handles all data traveling between 2 different NodeComponents. This includes distance.
	Not sure if this component can be totally replaced by a system, since this component needs access to NodeComponent and a TransformComponent
	Maybe it adds entities...but better would be to keep everything with components.

	Still not sure on event management etc.
**/

#pragma once
namespace np
{
	class ConnectionComponent :
		public ac::es::Component
	{
		AC_ES_COMPONENT(ConnectionComponent)
	public:

		np::NodeComponent node1;
		np::NodeComponent node2;

		std::vector<np::PulseComponent> pulses;

		ConnectionComponent( np::NodeComponent node1, np::NodeComponent node2)
		{
			this->node1 = node1;
			this->node2 = node2;
		}

		~ConnectionComponent(void)
		{
		}
		
		np::NodeComponent* getOtherNode( np::NodeComponent* node)
		{
			if ( node == &node1) return &node2;
			else if ( node == &node2) return &node1;
		}
	};
}