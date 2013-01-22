#include <ac\es.h>
#include <OgreEntity.h>
#include <OgreSceneNode.h>

#include <list>

/**
	GraphicComponent
	Graphics...holds an Ogre3d entity. The node property gets populated later, and will be used to remove this component from the scene.
**/

#pragma once
namespace np
{
	class GraphicComponent : public ac::es::Component
	{
		AC_ES_COMPONENT(GraphicComponent)
	public:

		std::list<Ogre::Entity*> entities;

		Ogre::Entity* entity;
		Ogre::SceneNode* node;

		GraphicComponent( Ogre::Entity* entities[], int numEntities);
		~GraphicComponent(void);

		void addEntity( Ogre::Entity* entity);
	};
}

