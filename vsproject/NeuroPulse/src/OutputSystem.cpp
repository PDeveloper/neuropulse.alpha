#include "OutputSystem.h"

#include <NodeComponent.h>
#include <OutputComponent.h>
#include <TransformComponent.h>
#include <ReactionComponent.h>
#include <BufferComponent.h>

#include <ResourcePacket.h>
#include <ResourceRequirement.h>

#include <list>
#include <algorithm>

#include <AdvancedOgreFramework.hpp>
#include <GameObjectFactory.h>

#include <PulseEvent.h>

#include <OgreOggSound.h>

np::OutputSystem::OutputSystem( np::EventManager* eventManager, np::NeuroWorldSettings* settings) :
	ac::es::EntityProcessingSystem( ac::es::ComponentFilter::Requires<BufferComponent>().requires<NodeComponent>().requires<OutputComponent>())
{
	this->eventManager = eventManager;
	this->pulseEvent = eventManager->getType( "pulseEvent");

	this->settings = settings;

	timeSinceLastPulse = 0.0;
	isPulsing = false;

	rawEnergy = np::ResourceManager::getSingletonPtr()->getType( "Energy");
	requirement = new np::ResourceRequirement( rawEnergy);
}


np::OutputSystem::~OutputSystem(void)
{
}

void np::OutputSystem::globalTick( double time)
{
	timeSinceLastPulse += time;
}

void np::OutputSystem::onBeginProcessing()
{
	if ( timeSinceLastPulse > settings->globalPulseTime)
	{
		timeSinceLastPulse -= settings->globalPulseTime;

		isPulsing = true;
	}
}

void np::OutputSystem::process( ac::es::EntityPtr e)
{
	NodeComponent* node = e->getComponent<NodeComponent>();
	BufferComponent* buffer = e->getComponent<BufferComponent>();
	OutputComponent* output = e->getComponent<OutputComponent>();
	TransformComponent* transform = e->getComponent<TransformComponent>();

	node->currentEnergy = buffer->getAmountOf( rawEnergy);

	//// CHECK IF NODE HAS ENOUGH ENERGY!!!
	if ( isPulsing && node->currentEnergy >= node->energyThreshold)
	{
		OgreOggSound::OgreOggISound* sound = OgreOggSound::OgreOggSoundManager::getSingletonPtr()->getSound( "PulseEmitted" + Ogre::StringConverter::toString( e->getId()));
		sound->setPlayPosition(0.0);
		sound->setPosition( transform->position);
		sound->play();

		//OgreFramework::getSingletonPtr()->m_pLog->logMessage("energy threshold reached");
		//OgreFramework::getSingletonPtr()->m_pLog->logMessage(Ogre::StringConverter::toString( (size_t)e->getId()));
		//OgreFramework::getSingletonPtr()->m_pLog->logMessage(Ogre::StringConverter::toString( (Ogre::Real)node->currentEnergy));
		//OgreFramework::getSingletonPtr()->m_pLog->logMessage(Ogre::StringConverter::toString( (Ogre::Real)node->energyThreshold));

		for (int i = 0; i < output->connections.size(); i++)
		{
			// Process all valid connections that were found.
			np::ConnectionBase* connection = output->connections.at(i);

			double tEnergy = std::max( getRawEnergy( connection->target), getThreshold( connection->target));

			if ( tEnergy < node->currentEnergy)
			{
				//OgreFramework::getSingletonPtr()->m_pLog->logMessage(Ogre::StringConverter::toString( connection->inPulseBuffer.size()));

				//OgreFramework::getSingletonPtr()->m_pLog->logMessage("Pulse Outputted!");
				//OgreFramework::getSingletonPtr()->m_pLog->logMessage(Ogre::StringConverter::toString( connection->target->node->parent->getId()));

				eventManager->dispatchEvent( new np::PulseEvent( pulseEvent, e, connection->target->parent));
			}
		}
		//OgreFramework::getSingletonPtr()->m_pLog->logMessage("energy left");
		//OgreFramework::getSingletonPtr()->m_pLog->logMessage(Ogre::StringConverter::toString( (Ogre::Real)node->currentEnergy));
		
		//OgreFramework::getSingletonPtr()->m_pLog->logMessage(Ogre::StringConverter::toString( (Ogre::Real)e->getComponent<np::ReactionComponent>()->output));
	}

	double ratio = buffer->getAmountOf( rawEnergy) / node->energyThreshold;
	if ( e->getId() == 5)
	{
		OgreFramework::getSingletonPtr()->m_pLog->logMessage( "ASDOIASJFIEJERGE");
		OgreFramework::getSingletonPtr()->m_pLog->logMessage( Ogre::StringConverter::toString( (float)ratio));
		OgreFramework::getSingletonPtr()->m_pLog->logMessage( Ogre::StringConverter::toString( Ogre::ColourValue( 0.1 * ratio, 0.1 * ratio, 1.0 * ratio)));
	}
	
	Ogre::MaterialPtr material = node->reactor->getSubEntity(0)->getMaterial();
	material->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setColourOperationEx(
		Ogre::LBX_SOURCE1,
		Ogre::LBS_MANUAL,
		Ogre::LBS_CURRENT,
		Ogre::ColourValue( 0.1 * ratio, 0.1 * ratio, 1.0 * ratio)
		);
	node->reactor->setMaterial( material);
}

void np::OutputSystem::onEndProcessing()
{
	isPulsing = false;
}

double np::OutputSystem::getRawEnergy( np::ConnectionBase* base )
{
	np::BufferComponent* buffer = base->parent->getComponent<np::BufferComponent>();
	return buffer->getAmountOf( rawEnergy);
}

double np::OutputSystem::getThreshold( np::ConnectionBase* base )
{
	np::NodeComponent* node = base->parent->getComponent<np::NodeComponent>();
	return node->energyThreshold;
}
