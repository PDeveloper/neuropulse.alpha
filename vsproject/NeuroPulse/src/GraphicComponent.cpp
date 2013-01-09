#include <GraphicComponent.h>

#include <AdvancedOgreFramework.hpp>

np::GraphicComponent::GraphicComponent( Ogre::Entity* entity)
{
	this->entity = entity;
}

np::GraphicComponent::~GraphicComponent(void)
{
	OgreFramework::getSingletonPtr()->m_pLog->logMessage( "graphic component destroyed");
}
