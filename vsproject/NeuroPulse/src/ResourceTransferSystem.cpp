#include "ResourceTransferSystem.h"
#include <ResourceOutputComponent.h>
#include <BufferComponent.h>
#include "AdvancedOgreFramework.hpp"
#include "PulseGateComponent.h"
#include "PulseComponent.h"

np::ResourceTransferSystem::ResourceTransferSystem(void) :
	ac::es::EntityProcessingSystem( ac::es::ComponentFilter::Requires<np::ResourceOutputComponent>().requires<np::BufferComponent>())
{
}

np::ResourceTransferSystem::~ResourceTransferSystem(void)
{

}

void np::ResourceTransferSystem::process( ac::es::EntityPtr e )
{
	np::ResourceOutputComponent* outputComponent	= e->getComponent<np::ResourceOutputComponent>();
	np::BufferComponent* bufferComponent			= e->getComponent<np::BufferComponent>();

	if ( outputComponent->target != NULL)
	{
		if ( e->containsComponent<np::BufferComponent>()) OgreFramework::getSingletonPtr()->m_pLog->logMessage( "I Has BufferComponent");
		if ( e->containsComponent<np::PulseGateComponent>()) OgreFramework::getSingletonPtr()->m_pLog->logMessage( "I Has PulseGateComponent");
		if ( e->containsComponent<np::PulseComponent>()) OgreFramework::getSingletonPtr()->m_pLog->logMessage( "I Has PulseComponent");
		OgreFramework::getSingletonPtr()->m_pLog->logMessage( Ogre::StringConverter::toString( e->getId()));
		if ( outputComponent->target->containsComponent<np::PulseGateComponent>()) OgreFramework::getSingletonPtr()->m_pLog->logMessage( "Has PulseGateComponent");
		if ( outputComponent->target->containsComponent<np::BufferComponent>()) OgreFramework::getSingletonPtr()->m_pLog->logMessage( "Has BufferComponent");
		np::BufferComponent* targetBufferComponent		= outputComponent->target->getComponent<np::BufferComponent>();

		double spaceLeft = targetBufferComponent->getNormalSpaceLeft();

		std::list<np::ResourcePacket*> packets = bufferComponent->getPackets( spaceLeft);

		if ( targetBufferComponent->addPackets( &packets) == PARTIAL)
		{
			bufferComponent->addPackets( &packets);
		}
	}
}
