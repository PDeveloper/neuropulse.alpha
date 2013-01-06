#include "OutputSystem.h"

#include <NodeComponent.h>
#include <OutputComponent.h>

#include <list>

np::OutputSystem::OutputSystem(void) :
	ac::es::EntityProcessingSystem( ac::es::ComponentFilter::Requires<NodeComponent>().requires<OutputComponent>())
{
}


np::OutputSystem::~OutputSystem(void)
{
}

void np::OutputSystem::process( ac::es::EntityPtr e)
{
	NodeComponent* node = e->getComponent<NodeComponent>();
	OutputComponent* output = e->getComponent<OutputComponent>();

	if ( node->currentEnergy > node->energyThreshold)
	{
		// List of all valid connections.
		// A valid connection is where the other node has less energy than the current node, so the current node can send it's pulses there.
		std::list<np::ConnectionComponent*> validConnections;
	
		// Determine valid target nodes!
		validConnections.clear();
		
		for (int i = 0; i < output->connections.size(); i++)
		{
			np::ConnectionComponent* connection = output->connections.at(i);
			np::NodeComponent* otherNode = connection->getOtherNode( node);

			if ( std::max<double>( otherNode->energyThreshold, otherNode->currentEnergy) < node->currentEnergy)
			{
				validConnections.push_back( connection);
			}
		}

		// Very inaccurate way of calculating the dispersed energy, but for now it could do.
		double dispersedEnergy = node->currentEnergy / validConnections.size();

		while ( !validConnections.empty())
		{
			// Process all valid connections that were found.
			np::ConnectionComponent* connection = validConnections.back();
			validConnections.pop_back();

			np::PulseComponent* pulse = new np::PulseComponent( dispersedEnergy, connection);

			// Pushes the pulse into the other nodes incoming buffer!
			np::NodeComponent* otherNode = connection->getOtherNode( node);
			otherNode->inPulseBuffer.push_back( pulse);
		}
	}
}