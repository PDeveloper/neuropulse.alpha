#include <ac\es.h>

#include <EventManager.h>
#include <NeuroWorldSettings.h>

#pragma once
namespace np
{
	class OutputSystem : public ac::es::EntityProcessingSystem
	{
		AC_ES_ENTITY_SYSTEM(OutputSystem)
	public:

		np::EventManager* eventManager;

		double timeSinceLastPulse;

		np::NeuroWorldSettings* settings;

		OutputSystem( np::EventManager* eventManager, np::NeuroWorldSettings* settings);
		~OutputSystem(void);

		void globalTick( double time);

	protected:
		void onBeginProcessing();
		void process( ac::es::EntityPtr e);
		void onEndProcessing();

	private:
		np::EventType* pulseEvent;

		bool isPulsing;
	};
}