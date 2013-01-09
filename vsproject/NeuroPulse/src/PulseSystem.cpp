#include "PulseSystem.h"

#include <PulseComponent.h>
#include <GraphicComponent.h>
#include <AnimationComponent.h>

#include <OgreSceneManager.h>
#include <AdvancedOgreFramework.hpp>

#include <list>
#include <PulseEvent.h>

np::PulseSystem::PulseSystem( np::GameObjectFactory* factory, np::EventManager* eventManager) :
	ac::es::EntityProcessingSystem( ac::es::ComponentFilter::Requires<PulseComponent>().requires<AnimationComponent>().requires<GraphicComponent>())
{
	this->factory = factory;

	this->eventManager = eventManager;
	this->pulseEvent = eventManager->getType( "pulseEvent");
}


np::PulseSystem::~PulseSystem(void)
{
}

void np::PulseSystem::onBeginProcessing()
{
	std::list<np::Event*>* pulseEvents = eventManager->getEvents( pulseEvent);

	for (std::list<np::Event*>::iterator it = pulseEvents->begin(); it != pulseEvents->end(); it++)
	{
		np::PulseEvent* e = static_cast<np::PulseEvent*>( (*it));

		factory->createPulseEntity( e->target1, e->target2);
	}
}

void np::PulseSystem::process( ac::es::EntityPtr e)
{
	np::AnimationComponent* animation = e->getComponent<AnimationComponent>();

	if ( !animation->isPlaying)
	{
		factory->killPulseEntity( e);
	}
}