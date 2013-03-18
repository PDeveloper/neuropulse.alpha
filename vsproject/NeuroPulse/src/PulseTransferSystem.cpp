#include "PulseTransferSystem.h"

#include <NodeComponent.h>
#include <OutputComponent.h>
#include <BufferComponent.h>
#include "AdvancedOgreFramework.hpp"

np::PulseTransferSystem::PulseTransferSystem(void) :
	ac::es::EntityProcessingSystem( ac::es::ComponentFilter::Requires<OutputComponent>().requires<NodeComponent>().requires<BufferComponent>())
{
	rawEnergy = np::ResourceManager::getSingletonPtr()->getType( "RawEnergy");
	requirement = new np::ResourceRequirement( rawEnergy);
}

np::PulseTransferSystem::~PulseTransferSystem(void)
{
}

void np::PulseTransferSystem::process( ac::es::EntityPtr e)
{
	np::NodeComponent* node = e->getComponent<NodeComponent>();
	np::OutputComponent* output = e->getComponent<OutputComponent>();
	np::BufferComponent* buffer = e->getComponent<BufferComponent>();

	int valid = 0;
	for (int i = 0; i < output->connections.size(); i++)
	{
		np::ConnectionBase* connection = output->connections[i];
		if ( !connection->outputPulses.empty()) valid++;
	}

	// Very inaccurate way of calculating the dispersed energy, but for now it could do.
	double dispersedEnergy = node->energyThreshold / double(valid);

	//dispersedEnergy *= 0.2;

	for ( int i = 0; i < output->connections.size(); i++)
	{
		np::ConnectionBase* connection = output->connections[i];
		if ( !connection->outputPulses.empty())
		{
			ac::es::EntityPtr pulse = connection->outputPulses[0];
			np::BufferComponent* pulseBuffer = pulse->getComponent<BufferComponent>();
			std::list<np::ResourcePacket*> packets = buffer->getPackets( dispersedEnergy, requirement);

			packets.front()->amount *= 0.2;

			//OgreFramework::getSingletonPtr()->m_pLog->logMessage( Ogre::StringConverter::toString( packets.size()));

			np::TransferSuccess result = pulseBuffer->addPackets( &packets);

			//OgreFramework::getSingletonPtr()->m_pLog->logMessage( Ogre::StringConverter::toString( Ogre::Real( pulseBuffer->getAmountOf( rawEnergy))));

			connection->outputPulse( pulse);
			connection->outputPulses.clear();

			connection->target->inputPulse( pulse);
			connection->target->parent->getComponent<BufferComponent>()->addPackets( &pulseBuffer->getPackets());
		}
	}
}
