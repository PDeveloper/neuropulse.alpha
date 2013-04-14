#include "HubConstructionComponent.h"
#include <GraphicComponent.h>
#include <Ogre.h>


np::HubConstructionComponent::HubConstructionComponent(void)
{
}


np::HubConstructionComponent::~HubConstructionComponent(void)
{
}

bool np::HubConstructionComponent::addToConstruction( np::NeuroPlayer* player, double amount)
{
	std::list<np::HubConstructionSlot>::iterator iterator;

	iterator = slots.begin();
	while ( iterator != slots.end())
	{
		np::HubConstructionSlot& slot = *iterator;

		if ( slot.player == player)
		{
			slot.amount += amount;

			np::GraphicComponent* graphic = slot.proxyHub->getComponent<np::GraphicComponent>();
			
			Ogre::Entity* entity = graphic->entities.front();
			Ogre::MaterialPtr material = entity->getSubEntity(0)->getMaterial();
			material->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(
				Ogre::LBX_SOURCE1,
				Ogre::LBS_MANUAL,
				Ogre::LBS_CURRENT,
				( slot.amount / 60.0) * 0.6);
			entity->setMaterial( material);

			if ( slot.amount >= 60.0)
			{
				return true;
			}

			return false;
		}

		iterator++;
	}

	return false;
}

void np::HubConstructionComponent::clear( void )
{
	slots.clear();
}

bool np::HubConstructionComponent::hasPlayer( np::NeuroPlayer* player )
{
	std::list<np::HubConstructionSlot>::iterator iterator;

	iterator = slots.begin();
	while ( iterator != slots.end())
	{
		if ( (*iterator).player == player) return true;
		iterator++;
	}

	return false;
}

void np::HubConstructionComponent::addPlayer( np::NeuroPlayer* player, ac::es::EntityPtr proxyHub )
{
	if ( !hasPlayer( player)) slots.push_back( np::HubConstructionSlot( player, 0.0, proxyHub));
}
