#include <ac\es.h>
#include <OgreSceneManager.h>

#pragma once
namespace np
{
	class ConnectionDisplaySystem : public ac::es::EntityProcessingSystem
	{
		AC_ES_ENTITY_SYSTEM(ConnectionDisplaySystem)
	public:
		Ogre::SceneManager* mSceneMgr;

		ConnectionDisplaySystem( Ogre::SceneManager* mSceneMgr);
		~ConnectionDisplaySystem(void);

	protected:
		void process( ac::es::EntityPtr e);
		void onAddedEntity( ac::es::EntityPtr e);
		void onRemovedEntity( ac::es::EntityPtr e);
	};
}