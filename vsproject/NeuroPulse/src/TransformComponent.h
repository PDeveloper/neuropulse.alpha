#include <ac\es.h>
#include <Ogre.h>

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
		{
			TransformComponent( 0, 0, 0);
		}

		TransformComponent( Ogre::Real x, Ogre::Real y, Ogre::Real z)
		{
			position.x = x;
			position.y = y;
			position.z = z;
		}

		~TransformComponent(void)
		{
		}
	};
}