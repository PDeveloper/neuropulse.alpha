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

	for (int i = 0; i < output->connections.size(); i++)
	{
		// Process all valid connections that were found.
		np::ConnectionBase* connection = output->connections.at(i);

		while ( !connection->inPulseBuffer.empty())
		{
			np::PulseComponent* pulse = connection->inPulseBuffer.back();
			connection->inPulseBuffer.pop_back();

			connection->inputPulse( pulse);
			node->currentEnergy += pulse->energy;
			delete pulse;
		}
	}

	if ( node->currentEnergy >= node->energyThreshold)
	{
		int valid = 0;
		for (int i = 0; i < output->connections.size(); i++) if ( output->connections.at(i)->isValid()) valid++;

		// Very inaccurate way of calculating the dispersed energy, but for now it could do.
		double dispersedEnergy = node->energyThreshold / double(valid);

		for (int i = 0; i < output->connections.size(); i++)
		{
			// Process all valid connections that were found.
			np::ConnectionBase* connection = output->connections.at(i);
			if ( connection->isValid())
			{
				np::PulseComponent* pulse = new np::PulseComponent( dispersedEnergy);

				connection->outputPulse( pulse);
				connection->target->inPulseBuffer.push_back( pulse);
			}
		}
	}
}