#pragma once
#include <ac/es.h>
#include <OgreCamera.h>
namespace np
{
	class CameraComponent : public ac::es::Component
	{
		AC_ES_COMPONENT(CameraComponent)
	public:

		Ogre::Camera* camera;

		CameraComponent( Ogre::Camera* camera);
	};
}
