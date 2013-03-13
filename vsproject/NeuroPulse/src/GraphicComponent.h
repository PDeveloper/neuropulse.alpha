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

		std::list<Ogre::MovableObject*> entities;
		Ogre::SceneNode* node;

		GraphicComponent( Ogre::MovableObject* entities[], int numEntities);
		~GraphicComponent(void);

		void addEntity( Ogre::MovableObject* entity);
	};
}

