#include "ReactionSystem.h"

#include <NodeComponent.h>
#include <ReactionComponent.h>

np::ReactionSystem::ReactionSystem(void) :
	ac::es::EntityProcessingSystem( ac::es::ComponentFilter::Requires<NodeComponent>().requires<ReactionComponent>())
{
}


np::ReactionSystem::~ReactionSystem(void)
{
}

void np::ReactionSystem::process( ac::es::EntityPtr e)
{
	NodeComponent* node = e->getComponent<NodeComponent>();
	ReactionComponent* reaction = e->getComponent<ReactionComponent>();

	node->currentEnergy += reaction->output;
}