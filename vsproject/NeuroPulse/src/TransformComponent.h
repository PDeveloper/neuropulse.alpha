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
	
		TransformComponent(void)
			: position( 0, 0, 0),
			rotation()
		{

		}

		TransformComponent( Ogre::Real x, Ogre::Real y, Ogre::Real z)
			: position( x, y, z),
			rotation()
		{

		}

		~TransformComponent(void)
		{
		}
	};
}