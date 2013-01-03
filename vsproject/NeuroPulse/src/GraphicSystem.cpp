#include "GraphicSystem.h"
#include "GraphicComponent.h"
#include "TransformComponent.h"

GraphicSystem::GraphicSystem() :
	ac::es::EntityProcessingSystem( ac::es::ComponentFilter::Requires<GraphicComponent>().requires<TransformComponent>())
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
	graphic->node->setOrientation( *transform->rotation);
}