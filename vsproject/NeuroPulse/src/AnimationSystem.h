#include <ac\es.h>

#pragma once
namespace np
{

	class NeuroWorld;

	class AnimationSystem : public ac::es::EntityProcessingSystem
	{
		AC_ES_ENTITY_SYSTEM(AnimationSystem)
	public:

		double animationSpeed;

		np::NeuroWorld* world;

		AnimationSystem(np::NeuroWorld* world);
		~AnimationSystem(void);

	protected:
		virtual void process( ac::es::EntityPtr e);
	};
}