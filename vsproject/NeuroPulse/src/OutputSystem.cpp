#include "OutputSystem.h"

#include <NodeComponent.h>
#include <OutputComponent.h>
#include <TransformComponent.h>
#include <ReactionComponent.h>

#include <list>

#include <AdvancedOgreFramework.hpp>
#include <GameObjectFactory.h>

#include <PulseEvent.h>

np::OutputSystem::OutputSystem( np::EventManager* eventManager) :
	ac::es::EntityProcessingSystem( ac::es::ComponentFilter::Requires<NodeComponent>().requires<OutputComponent>())
{
	this->eventManager = eventManager;
	this->pulseEvent = eventManager->getType( "pulseEvent");
}


np::OutputSystem::~OutputSystem(void)
{
}

void np::OutputSystem::process( ac::es::EntityPtr e)
{
	NodeComponent* node = e->getComponent<NodeComponent>();
	OutputComponent* output = e->getComponent<OutputComponent>();
	TransformComponent* transform = e->getComponent<TransformComponent>();

	if ( node->currentEnergy >= node->energyThreshold)
	{
		OgreFramework::getSingletonPtr()->m_pLog->logMessage("energy threshold reached");
		OgreFramework::getSingletonPtr()->m_pLog->logMessage(Ogre::StringConverter::toString( (size_t)e->getId()));
		OgreFramework::getSingletonPtr()->m_pLog->logMessage(Ogre::StringConverter::toString( (Ogre::Real)node->currentEnergy));
		OgreFramework::getSingletonPtr()->m_pLog->logMessage(Ogre::StringConverter::toString( (Ogre::Real)node->energyThreshold));
		int valid = 0;
		for (int i = 0; i < output->connections.size(); i++) if ( output->connections.at(i)->isValid()) valid++;

		// Very inaccurate way of calculating the dispersed energy, but for now it could do.
		double dispersedEnergy = node->energyThreshold / double(valid);
		dispersedEnergy *= 0.5;

		for (int i = 0; i < output->connections.size(); i++)
		{
			// Process all valid connections that were found.
			np::ConnectionBase* connection = output->connections.at(i);
			if ( connection->isValid())
			{
				np::Pulse* pulse = new np::Pulse( dispersedEnergy);

				connection->outputPulse( pulse);
				connection->target->inPulseBuffer.push_back( pulse);
				OgreFramework::getSingletonPtr()->m_pLog->logMessage(Ogre::StringConverter::toString( connection->inPulseBuffer.size()));

				np::TransformComponent* transform1 = output->parent->getComponent<np::TransformComponent>();
				np::TransformComponent* transform2 = connection->target->node->parent->getComponent<np::TransformComponent>();

				OgreFramework::getSingletonPtr()->m_pLog->logMessage("Pulse Outputted!");
				OgreFramework::getSingletonPtr()->m_pLog->logMessage(Ogre::StringConverter::toString( connection->target->node->parent->getId()));

				eventManager->dispatchEvent( new np::PulseEvent( pulseEvent, transform1->position, transform2->position));
			}
		}

		if ( valid > 0) node->currentEnergy -= node->energyThreshold;

		OgreFramework::getSingletonPtr()->m_pLog->logMessage("energy left");
		OgreFramework::getSingletonPtr()->m_pLog->logMessage(Ogre::StringConverter::toString( (Ogre::Real)node->currentEnergy));
		
		OgreFramework::getSingletonPtr()->m_pLog->logMessage(Ogre::StringConverter::toString( (Ogre::Real)e->getComponent<np::ReactionComponent>()->output));
	}

	for (int i = 0; i < output->connections.size(); i++)
	{
		// Process all valid connections that were found.
		np::ConnectionBase* connection = output->connections.at(i);

		while ( !connection->inPulseBuffer.empty())
		{
			np::Pulse* pulse = connection->inPulseBuffer.back();
			connection->inPulseBuffer.pop_back();

			OgreFramework::getSingletonPtr()->m_pLog->logMessage("input energy pulse!");
			OgreFramework::getSingletonPtr()->m_pLog->logMessage(Ogre::StringConverter::toString( (size_t)e->getId()));

			connection->inputPulse( pulse);
			node->currentEnergy += pulse->energy;
			delete pulse;
		}
	}

}