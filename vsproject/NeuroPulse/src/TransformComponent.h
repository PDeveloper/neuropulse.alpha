#include <ac\es.h>
#include <Ogre.h>

/**
	TransformComponent
	Holds positional and rotational information about an Entity.
**/

#pragma once
namespace np
{
	class TransformComponent : public ac::es::Component
	{
		AC_ES_COMPONENT(TransformComponent)
	public:
	
		Ogre::Vector3 position;
		Ogre::Quaternion rotation;
		Ogre::Vector3 scale;
	
		TransformComponent(void);
		TransformComponent( Ogre::Real x, Ogre::Real y, Ogre::Real z);
		~TransformComponent(void);
	};
}