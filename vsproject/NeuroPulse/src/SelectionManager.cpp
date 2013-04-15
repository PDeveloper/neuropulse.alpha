#include "SelectionManager.h"
#include <NodeComponent.h>
#include <ConstructComponent.h>
#include <ResourceInputComponent.h>
#include <ResourceOutputComponent.h>

np::SelectionManager::SelectionManager(void)
{
}

np::SelectionManager::~SelectionManager(void)
{
}

void np::SelectionManager::pushNode( Ogre::Entity* node )
{
	selectionList.push_back( node);
}

ac::es::EntityPtr np::SelectionManager::popNode()
{
	if ( selectionList.empty()) return NULL;

	ac::es::EntityPtr e;

	e = getEntityPtr( selectionList.back());
	bool isNode = (e != NULL && e->containsComponent<np::NodeComponent>());

	while ( !isNode)
	{
		selectionList.pop_back();

		e = getEntityPtr( selectionList.back());
		isNode = (e != NULL && e->containsComponent<np::NodeComponent>());
	}

	selectionList.pop_back();

	return e;
}

void np::SelectionManager::popUntilNode()
{
	if ( !selectionList.empty())
	{
		ac::es::EntityPtr e = getEntityPtr( selectionList.back());
		bool isNode = ( e != NULL && e->containsComponent<np::NodeComponent>());

		while ( !isNode)
		{
			selectionList.pop_back();

			e = getEntityPtr( selectionList.back());
			isNode = e->containsComponent<np::NodeComponent>();
		}
	}
}

ac::es::EntityPtr np::SelectionManager::getLastNode()
{
	if ( !selectionList.empty())
	{
		std::list<Ogre::Entity*>::reverse_iterator itr;
		ac::es::EntityPtr e;

		for( itr = selectionList.rbegin(); itr != selectionList.rend(); itr++)
		{
			e = getEntityPtr( (*itr));
			if ( e != NULL && e->containsComponent<np::NodeComponent>()) return e;
		}
	}

	return NULL;
}

void np::SelectionManager::pushConstruct( Ogre::Entity* construct )
{
	selectionList.push_back( construct);
}

ac::es::EntityPtr np::SelectionManager::popConstruct()
{
	ac::es::EntityPtr e = getEntityPtr( selectionList.back());
	bool isConstruct = e->containsComponent<np::ConstructComponent>();

	while ( !isConstruct)
	{
		selectionList.pop_back();

		e = getEntityPtr( selectionList.back());
		if ( e != NULL) isConstruct = e->containsComponent<np::ConstructComponent>();
	}

	selectionList.pop_back();

	return e;
}

void np::SelectionManager::pushResourceBud( Ogre::Entity* bud )
{
	selectionList.push_back( bud);
}

ac::es::EntityPtr np::SelectionManager::popResourceBud()
{
	ac::es::EntityPtr e = getEntityPtr( selectionList.back());
	bool isBud = e->containsComponent<np::ResourceInputComponent>() || e->containsComponent<np::ResourceOutputComponent>();

	while ( !isBud)
	{
		selectionList.pop_back();

		e = getEntityPtr( selectionList.back());
		if ( e != NULL) isBud = e->containsComponent<np::ResourceInputComponent>() || e->containsComponent<np::ResourceOutputComponent>();
	}

	selectionList.pop_back();

	return e;
}

void np::SelectionManager::pushConstructConnection( Ogre::Entity* constructConnection )
{
	selectionList.push_back( constructConnection);
}

ac::es::EntityPtr np::SelectionManager::popConstructConnection()
{
	ac::es::EntityPtr e = getEntityPtr( selectionList.back());
	bool isBud = e->containsComponent<np::ResourceInputComponent>() || e->containsComponent<np::ResourceOutputComponent>();

	while ( !isBud)
	{
		selectionList.pop_back();

		e = getEntityPtr( selectionList.back());
		if ( e != NULL) isBud = e->containsComponent<np::ResourceInputComponent>() || e->containsComponent<np::ResourceOutputComponent>();
	}

	selectionList.pop_back();

	return e;
}

ac::es::EntityPtr np::SelectionManager::getEntityPtr( Ogre::Entity* entity )
{
	const Ogre::Any& entityAny = entity->getUserObjectBindings().getUserAny("Entity");
	if ( !entityAny.isEmpty())
	{
		return entityAny.get<ac::es::EntityPtr>();
	}

	return NULL;
}

bool np::SelectionManager::hasEntityPtr( Ogre::Entity* entity )
{
	const Ogre::Any& entityAny = entity->getUserObjectBindings().getUserAny("Entity");
	if ( !entityAny.isEmpty()) return true;

	return false;
}

ac::es::EntityPtr np::SelectionManager::getLastOf( ac::es::ComponentFilter filter)
{
	return NULL;
}

Ogre::Entity* np::SelectionManager::getLast()
{
	if ( selectionList.empty()) return NULL;

	return selectionList.back();
}
