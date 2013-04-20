#include <OgreEntity.h>
#include <ac/es.h>

#include <stack>

#pragma once
namespace np
{
	class SelectionManager
	{
	public:

		Ogre::Entity* getLast();
		ac::es::EntityPtr getLastOf( ac::es::ComponentFilter filter);

		void pushNode(Ogre::Entity* node);
		ac::es::EntityPtr popNode();
		void popUntilNode();
		ac::es::EntityPtr getLastNode();

		void pushConstruct(Ogre::Entity* construct);
		ac::es::EntityPtr popConstruct();
		void pushResourceBud(Ogre::Entity* bud);
		ac::es::EntityPtr popResourceBud();
		void pushConstructConnection(Ogre::Entity* constructConnection);
		ac::es::EntityPtr popConstructConnection();

		bool hasEntityPtr( Ogre::Entity* entity);
		ac::es::EntityPtr getEntityPtr( Ogre::Entity* entity);

		SelectionManager(void);
		~SelectionManager(void);
		void clean();
	private:
		std::list<Ogre::Entity*> selectionList;
	};
}

