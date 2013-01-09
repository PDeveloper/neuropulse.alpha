#include <string>

#include <map>
#include <vector>
#include <list>

#include <Event.h>
#include <EventType.h>

#pragma once
namespace np
{
	class EventManager
	{
	public:

		std::map< std::string, np::EventType*> types;

		std::vector<std::list<np::Event*>*> eventBuffers;

		EventManager(void);
		~EventManager(void);

		np::EventType* getType( std::string id);

		void dispatchEvent( np::Event* e);

		std::list<np::Event*>* getEvents( np::EventType* type);

		void refresh();
	};
}

