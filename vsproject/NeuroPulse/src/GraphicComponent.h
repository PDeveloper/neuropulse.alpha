#include <ac\es.h>
#include <OgreEntity.h>
#include <OgreSceneNode.h>

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
		Ogre::Entity* entity;
		Ogre::SceneNode* node;

		GraphicComponent( Ogre::Entity* entity)
		{
			this->entity = entity;
		}

		~GraphicComponent(void)
		{
		}
	};
}

