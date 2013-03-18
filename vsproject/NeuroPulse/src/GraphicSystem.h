#include <ac\es.h>
#include <OgreSceneManager.h>

#pragma once
namespace np
{

	class GraphicComponent;

	class GraphicSystem : public ac::es::EntityProcessingSystem
	{
		AC_ES_ENTITY_SYSTEM(GraphicSystem)
	public:
		Ogre::SceneManager* mSceneMgr;

		GraphicSystem( Ogre::SceneManager* mSceneMgr);
		~GraphicSystem(void);
	protected:
		void process( ac::es::EntityPtr e);
		void onAddedEntity( ac::es::EntityPtr e);
		void addChildren( np::GraphicComponent* parent, np::GraphicComponent* child);
		void onRemovedEntity( ac::es::EntityPtr e);
	};
}

// register the MovementSystem
//AC_ES_REGISTER_ENTITY_SYSTEM(np::GraphicSystem)
