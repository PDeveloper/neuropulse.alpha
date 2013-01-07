#include <ac\es.h>
#include <vector>

#include <TweenState.h>

/**
	ConnectionComponent
	This component handles all data traveling between 2 different NodeComponents. This includes distance.
	Not sure if this component can be totally replaced by a system, since this component needs access to NodeComponent and a TransformComponent
	Maybe it adds entities...but better would be to keep everything with components.

	Still not sure on event management etc.
**/

#pragma once
namespace np
{

	class AnimationComponent :
		public ac::es::Component
	{
		AC_ES_COMPONENT(AnimationComponent)
	public:

		std::vector<np::TweenState> states;

		double t;
		int segment;

		bool isPlaying;
		bool isLooping;

		AnimationComponent( np::TweenState states[], int numStates);
		~AnimationComponent(void);
		
		void play(void);
		void pause(void);
		void stop(void);
		
	};
}