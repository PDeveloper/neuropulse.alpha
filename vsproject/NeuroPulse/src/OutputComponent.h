#include <ac\es.h>
#include <vector>
#include <array>

#include <math.h>

#include <ConnectionComponent.h>
#include <PulseComponent.h>
#include <NodeComponent.h>

/**
	ReactionComponent
	Since not all nodes will have a constant increase in energy, this component handles the increase. Add it to live nodes, dead nodes just
	don't have it.
**/

#pragma once
namespace np
{
	class OutputComponent :
		public ac::es::Component
	{
		AC_ES_COMPONENT(OutputComponent)
	public:

		std::vector<np::ConnectionComponent> connections;
		std::vector<bool> validConnections;

		np::NodeComponent* parent;

		OutputComponent( ConnectionComponent connections[], np::NodeComponent* parent)
			: connections( connections, connections + sizeof(connections) / sizeof(connections[0]) ),
			validConnections( sizeof(connections) / sizeof(connections[0]))
		{
			this->parent = parent;
		}

		~OutputComponent(void)
		{
		}

		void pump( double energy)
		{
			int numValidConnections = 0;
			
			for ( int i = 0; i < connections.size(); i++)
			{
				validConnections.at( i) = false;
				np::NodeComponent* otherNode = connections.at( i).getOtherNode( parent);

				if ( std::max<double>( otherNode->energyThreshold, otherNode->currentEnergy) < energy)
				{
					validConnections.at( i) = true;
					numValidConnections++;
				}
			}

			double dispersedEnergy = energy / numValidConnections;
		}

	};

}