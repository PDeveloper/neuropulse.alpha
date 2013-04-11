#include "ResourceTransferSystem.h"
#include <ResourceOutputComponent.h>
#include <BufferComponent.h>

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
		np::BufferComponent* targetBufferComponent		= outputComponent->target->getComponent<np::BufferComponent>();

		double spaceLeft = targetBufferComponent->getNormalSpaceLeft();

		std::list<np::ResourcePacket*> packets = bufferComponent->getPackets( spaceLeft);

		if ( targetBufferComponent->addPackets( &packets) == PARTIAL)
		{
			bufferComponent->addPackets( &packets);
		}
	}
}
