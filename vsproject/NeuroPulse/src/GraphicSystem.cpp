#include "GraphicSystem.h"
#include "GraphicComponent.h"
#include "TransformComponent.h"

GraphicSystem::GraphicSystem(void)
	: ac::es::EntityProcessingSystem( ac::es::ComponentFilter::Requires<GraphicComponent>().requires<TransformComponent>())
{
}


GraphicSystem::~GraphicSystem(void)
{
}

void GraphicSystem::process( ac::es::Entity& e)
{
	GraphicComponent* graphic = e.getComponent<GraphicComponent>();
	TransformComponent* transform = e.getComponent<TransformComponent>();

	graphic->node->setPosition( transform->x, transform->y, transform->z);
	//the order of rotations might be fucked... ->
	graphic->node->yaw( Ogre::Degree( transform->rotationY));
	graphic->node->pitch( Ogre::Degree( transform->rotationX));
	graphic->node->roll( Ogre::Degree( transform->rotationZ));
}