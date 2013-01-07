#include <OgreVector3.h>

#pragma once
namespace np
{
	class TweenState
	{
	public:

		Ogre::Vector3 target;
		
		double duration;

		TweenState( Ogre::Vector3 target, double duration)
			:target( target)
		{
			this->duration = duration;
		}

		~TweenState(void)
		{
		}
	};
}

