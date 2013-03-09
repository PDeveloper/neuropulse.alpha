#include "ReactionSystem.h"

#include <NodeComponent.h>
#include <ReactionComponent.h>
#include <TransformComponent.h>

np::ReactionSystem::ReactionSystem() :
	ac::es::EntityProcessingSystem( ac::es::ComponentFilter::Requires<NodeComponent>().requires<ReactionComponent>())
{
	deltaTime = 0.0;
}


np::ReactionSystem::~ReactionSystem(void)
{
}

void np::ReactionSystem::setDeltaTime( double time)
{
	deltaTime = time;
}

void np::ReactionSystem::process( ac::es::EntityPtr e)
{
	NodeComponent* node = e->getComponent<NodeComponent>();
	ReactionComponent* reaction = e->getComponent<ReactionComponent>();

	node->currentEnergy += reaction->output * ( deltaTime / 1000.0);

	//// DEBUGGING ONLY!!!!!
	//np::TransformComponent* transform = e->getComponent<np::TransformComponent>();
	//transform->position.y = node->currentEnergy * 0.5;
	////
}