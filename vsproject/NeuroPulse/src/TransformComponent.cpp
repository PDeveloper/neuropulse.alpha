#include <TransformComponent.h>

np::TransformComponent::TransformComponent(void)
	: position( 0, 0, 0),
	rotation()
{

}

np::TransformComponent::TransformComponent( Ogre::Real x, Ogre::Real y, Ogre::Real z)
	: position( x, y, z),
	rotation()
{

}

np::TransformComponent::~TransformComponent(void)
{
}