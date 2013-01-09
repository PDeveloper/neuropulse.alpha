#include <ac\es.h>

#include <EventManager.h>

#include <GameObjectFactory.h>

#pragma once
namespace np
{
	class PulseSystem : public ac::es::EntityProcessingSystem
	{
		AC_ES_ENTITY_SYSTEM(PulseSystem)
	public:

		np::EventManager* eventManager;
		np::GameObjectFactory* factory;

		PulseSystem( np::GameObjectFactory* factory, np::EventManager* eventManager);
		~PulseSystem(void);

	protected:
		void onBeginProcessing();
		void process( ac::es::EntityPtr e);

	private:
		np::EventType* pulseEvent;
	};
}