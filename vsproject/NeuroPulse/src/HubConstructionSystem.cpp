#include "HubConstructionSystem.h"

#include <NodeComponent.h>
#include <BufferComponent.h>
#include <HubComponent.h>
#include <HubConstructionComponent.h>
#include <GraphicComponent.h>

#include <ResourceManager.h>
#include <NeuroWorld.h>
#include <AdvancedOgreFramework.hpp>

np::HubConstructionSystem::HubConstructionSystem(np::NeuroWorld* world) :
	ac::es::EntityProcessingSystem( ac::es::ComponentFilter::Requires<BufferComponent>().requires<NodeComponent>().requires<HubConstructionComponent>()),
	hubSchematicRequirement(np::ResourceManager::getSingletonPtr()->getType( "HubSchematic"))
{
	this->world = world;
}

np::HubConstructionSystem::~HubConstructionSystem(void)
{
}

void np::HubConstructionSystem::process( ac::es::EntityPtr e )
{
	np::NodeComponent* node = e->getComponent<np::NodeComponent>();
	np::HubConstructionComponent* construction = e->getComponent<np::HubConstructionComponent>();
	np::BufferComponent* buffer = e->getComponent<np::BufferComponent>();

	if ( !e->containsComponent<np::HubComponent>())
	{
		std::list<np::ResourcePacket*> packets = buffer->getPackets( hubSchematicRequirement);

		std::list<np::ResourcePacket*>::iterator iterator;
		iterator = packets.begin();
		while ( iterator != packets.end())
		{
			np::ResourcePacket* packet = *iterator;
			np::NeuroPlayer* player = world->settings->getPlayerFromSignature( packet->signature.getBits());

			if ( player != NULL)
			{
				if ( !construction->hasPlayer( player))
				{
					ac::es::EntityPtr proxyHub = world->gameObjectFactory->createProxyHubEntity( e, player);
					construction->addPlayer( player, proxyHub);
				}

				if ( construction->addToConstruction( player, packet->amount))
				{
					std::list<np::HubConstructionSlot>::iterator iterator2;
					iterator2 = construction->slots.begin();
					while ( iterator2 != construction->slots.end())
					{
						world->gameObjectFactory->killProxyHubEntity( (*iterator2).proxyHub);

						iterator2++;
					}

					world->gameObjectFactory->createHub( e, player);

					construction->clear();
					return;
				}
			}

			iterator++;
		}
	}
}
