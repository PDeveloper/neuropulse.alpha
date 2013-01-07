#include "AnimationComponent.h"

#include <AdvancedOgreFramework.hpp>

np::AnimationComponent::AnimationComponent( np::TweenState states[], int numStates)
	: states( states, states + numStates )
{
	segment = 0;
	t = 0.0;

	isPlaying = true;
	isLooping = true;

	OgreFramework::getSingletonPtr()->m_pLog->logMessage(Ogre::StringConverter::toString(this->states.size()));
	OgreFramework::getSingletonPtr()->m_pLog->logMessage(Ogre::StringConverter::toString(sizeof(states[0])));
}

np::AnimationComponent::~AnimationComponent(void)
{
}

void np::AnimationComponent::play(void)
{
	isPlaying = true;
}

void np::AnimationComponent::pause(void)
{
	isPlaying = false;
}

void np::AnimationComponent::stop(void)
{
	isPlaying = false;

	segment = 0;
	t = 0.0;
}