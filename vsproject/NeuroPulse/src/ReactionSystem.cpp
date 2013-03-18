#include "ReactionSystem.h"

#include <NodeComponent.h>
#include <ReactionComponent.h>
#include <BufferComponent.h>
#include <TransformComponent.h>

#include <ResourcePacket.h>

np::ReactionSystem::ReactionSystem() :
	ac::es::EntityProcessingSystem( ac::es::ComponentFilter::Requires<BufferComponent>().requires<ReactionComponent>())
{
	deltaTime = 0.0;
	rawEnergy = np::ResourceManager::getSingletonPtr()->getType( "RawEnergy");
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
	BufferComponent* buffer = e->getComponent<BufferComponent>();
	ReactionComponent* reaction = e->getComponent<ReactionComponent>();

	buffer->appendPacket( new np::ResourcePacket( rawEnergy, reaction->output * ( deltaTime / 1000.0)));

	//// DEBUGGING ONLY!!!!!
	//np::TransformComponent* transform = e->getComponent<np::TransformComponent>();
	//transform->position.y = node->currentEnergy * 0.5;
	////
}