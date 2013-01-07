#include "AnimationSystem.h"

#include <AnimationComponent.h>
#include <TransformComponent.h>


np::AnimationSystem::AnimationSystem(void) :
	ac::es::EntityProcessingSystem( ac::es::ComponentFilter::Requires<AnimationComponent>().requires<TransformComponent>()),
	animationSpeed( 0.02)
{
}


np::AnimationSystem::~AnimationSystem(void)
{
}

void np::AnimationSystem::process( ac::es::EntityPtr e)
{
	TransformComponent* transform = e->getComponent<TransformComponent>();
	AnimationComponent* animation = e->getComponent<AnimationComponent>();

	if ( animation->isPlaying)
	{
		np::TweenState current = animation->states.at( animation->segment);
		np::TweenState next = animation->states.at( animation->segment + 1);

		double dx = next.target.x - current.target.x;
		double dy = next.target.y - current.target.y;
		double dz = next.target.z - current.target.z;

		transform->position.x = current.target.x + animation->t * dx;
		transform->position.y = current.target.y + animation->t * dy;
		transform->position.z = current.target.z + animation->t * dz;

		animation->t += ( animationSpeed / next.duration);

		if ( animation->t > 1.0)
		{
			animation->segment++;
			animation->t = 0.0;

			if ( animation->segment == animation->states.size() - 1)
			{
				animation->stop();
				if ( animation->isLooping) animation->play();
			}
		}
	}
}