#include "ConstructConnectionSystem.h"

#include <TransformComponent.h>
#include <ConstructConnectionComponent.h>
#include <GraphicComponent.h>

np::ConstructConnectionSystem::ConstructConnectionSystem(void) :
	ac::es::EntityProcessingSystem( ac::es::ComponentFilter::Requires<ConstructConnectionComponent>().requires<TransformComponent>())
{
}

np::ConstructConnectionSystem::~ConstructConnectionSystem(void)
{
}

void np::ConstructConnectionSystem::process( ac::es::EntityPtr e)
{
	np::ConstructConnectionComponent* constructConnection = e->getComponent<np::ConstructConnectionComponent>();
	np::TransformComponent* connectionTransform = e->getComponent<np::TransformComponent>();

	np::GraphicComponent* g1 = constructConnection->entity1->getComponent<np::GraphicComponent>();
	np::GraphicComponent* g2 = constructConnection->entity2->getComponent<np::GraphicComponent>();

	if ( g1 != NULL && g1->node != NULL && g2 != NULL && g2->node != NULL)
	{
		double d = g1->node->_getDerivedPosition().distance( g2->node->_getDerivedPosition()) / 100.0;

		connectionTransform->position = g1->node->_getDerivedPosition();
		connectionTransform->rotation = Ogre::Vector3::UNIT_Z.getRotationTo( g2->node->_getDerivedPosition() - g1->node->_getDerivedPosition());
		connectionTransform->scale = Ogre::Vector3( 1.0, 1.0, d);
	}
}
