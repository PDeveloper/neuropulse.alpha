#include <ac\es.h>
#include <OgreQuaternion.h>

#pragma once
class TransformComponent : public ac::es::Component
{
	AC_ES_COMPONENT(TransformComponent)
public:

	float x;
	float y;
	float z;

	Ogre::Quaternion* rotation;
	
	TransformComponent(void)
	{
		x = y = z = 0.0;
		rotation = new Ogre::Quaternion();
	}

	~TransformComponent(void)
	{
	}
};

