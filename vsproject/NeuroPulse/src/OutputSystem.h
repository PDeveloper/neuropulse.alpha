#include <ac\es.h>

#include <EventManager.h>

#pragma once
namespace np
{
	class OutputSystem : public ac::es::EntityProcessingSystem
	{
		AC_ES_ENTITY_SYSTEM(OutputSystem)
	public:

		np::EventManager* eventManager;

		OutputSystem( np::EventManager* eventManager);
		~OutputSystem(void);

	protected:
		virtual void process( ac::es::EntityPtr e);

	private:
		np::EventType* pulseEvent;
	};
}