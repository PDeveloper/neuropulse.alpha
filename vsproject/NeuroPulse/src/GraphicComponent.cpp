#include <GraphicComponent.h>

#include <AdvancedOgreFramework.hpp>

np::GraphicComponent::GraphicComponent( Ogre::MovableObject* entities[], int numEntities) :
	entities( entities, entities + numEntities )
{
}

np::GraphicComponent::~GraphicComponent(void)
{
	OgreFramework::getSingletonPtr()->m_pLog->logMessage( "graphic component destroyed");


}

void np::GraphicComponent::addEntity( Ogre::Entity* entity)
{
	entities.push_back( entity);
}