#include "EventManager.h"

#include <Event.h>
#include <EventType.h>

np::EventManager::EventManager(void) :
	eventBuffers()
{
}


np::EventManager::~EventManager(void)
{
}

np::EventType* np::EventManager::getType( std::string id)
{
	if ( types[id] == NULL)
	{
		types[id] = new np::EventType( eventBuffers.size());
		eventBuffers.push_back( new std::list<np::Event*>());
	}

	return types[id];
}

void np::EventManager::dispatchEvent( np::Event* e)
{
	eventBuffers.at( e->type->id)->push_back( e);
}

std::list<np::Event*>* np::EventManager::getEvents( np::EventType* type)
{
	return eventBuffers.at( type->id);
}

void np::EventManager::refresh()
{
	for ( int i = 0; i < eventBuffers.size(); i++)
	{
		std::list<np::Event*>* clist = eventBuffers.at(i);

		// Destroy all event objects.
		for (std::list<np::Event*>::iterator it = clist->begin(); it != clist->end(); it++) delete (*it);

		clist->clear();
	}
}