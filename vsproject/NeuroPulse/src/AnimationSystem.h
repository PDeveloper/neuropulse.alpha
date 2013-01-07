#include <ac\es.h>

#pragma once
namespace np
{
	class AnimationSystem : public ac::es::EntityProcessingSystem
	{
		AC_ES_ENTITY_SYSTEM(AnimationSystem)
	public:

		double animationSpeed;

		AnimationSystem(void);
		~AnimationSystem(void);

	protected:
		virtual void process( ac::es::EntityPtr e);
	};
}