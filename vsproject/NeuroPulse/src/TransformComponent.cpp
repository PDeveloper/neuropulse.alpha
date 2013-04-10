#include <TransformComponent.h>

np::TransformComponent::TransformComponent(void) :
	position( 0, 0, 0),
	rotation(),
	scale( 1.0, 1.0, 1.0)
{

}

np::TransformComponent::TransformComponent( Ogre::Real x, Ogre::Real y, Ogre::Real z) :
	position( x, y, z),
	rotation(),
	scale( 1.0, 1.0, 1.0)
{

}

np::TransformComponent::~TransformComponent(void)
{
}