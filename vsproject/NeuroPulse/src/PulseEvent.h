#include <Event.h>

#include <OgreVector3.h>

#pragma once
namespace np
{
	class PulseEvent : public np::Event
	{
	public:

		Ogre::Vector3& target1;
		Ogre::Vector3& target2;

		PulseEvent( np::EventType* type, Ogre::Vector3& target1, Ogre::Vector3& target2) :
			np::Event( type),
			target1( target1),
			target2( target2)
		{
		}

		~PulseEvent(void)
		{
		}
	};
}

