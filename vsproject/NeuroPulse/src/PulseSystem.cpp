#include "PulseSystem.h"

#include <PulseComponent.h>
#include <GraphicComponent.h>
#include <AnimationComponent.h>
#include <TransformComponent.h>

#include <OutputComponent.h>

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
		
		np::PulseEvent* event = static_cast<np::PulseEvent*>( *it);

		np::TransformComponent* t1 = event->target1->getComponent<np::TransformComponent>();
		np::TransformComponent* t2 = event->target2->getComponent<np::TransformComponent>();

		np::OutputComponent* output1 = event->target1->getComponent<np::OutputComponent>();

		ac::es::EntityPtr pulse = factory->createPulseEntity( t1->position, t2->position);

		

		output1->getConnection( event->target2)->outputPulses.push_back( pulse);


	}
}

void np::PulseSystem::process( ac::es::EntityPtr e)
{
	np::AnimationComponent* animation = e->getComponent<AnimationComponent>();

	if ( !animation->isPlaying)
	{
		factory->releasePulseEntity( e);
	}

	
}