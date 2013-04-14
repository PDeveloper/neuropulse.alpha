#include "CameraControlSystem.h"
#include <CameraComponent.h>
#include <TransformComponent.h>
#include <NeuroWorld.h>

np::CameraControlSystem::CameraControlSystem( np::NeuroWorld* world) :
	ac::es::EntityProcessingSystem( ac::es::ComponentFilter::Requires<CameraComponent>().requires<TransformComponent>())
{
	this->world = world;
}


np::CameraControlSystem::~CameraControlSystem(void)
{
}

void np::CameraControlSystem::process( ac::es::EntityPtr e )
{
	np::TransformComponent* transform = e->getComponent<TransformComponent>();
	np::CameraComponent* camera = e->getComponent<CameraComponent>();

	double p = world->timeSinceLastUpdate / 400.0;

	camera->camera->setOrientation( Ogre::Quaternion::Slerp( 0.9999 * p, camera->camera->getOrientation(), transform->rotation, true));
	camera->camera->move( 0.9999 * p * ( transform->position - camera->camera->getPosition()));
}
