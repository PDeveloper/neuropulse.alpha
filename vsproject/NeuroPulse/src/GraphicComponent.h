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

		np::GraphicComponent* parent;
		std::list<np::GraphicComponent*> children;

		std::list<Ogre::MovableObject*> entities;

		Ogre::SceneNode* node;

		bool isDirty;

		GraphicComponent( Ogre::MovableObject* entities[], int numEntities);
		~GraphicComponent(void);

		void addEntity( Ogre::Entity* entity);
		void removeEntity( Ogre::Entity* entity);

		void addChild( np::GraphicComponent* graphic);
		void removeChild( np::GraphicComponent* graphic);
	};
}

