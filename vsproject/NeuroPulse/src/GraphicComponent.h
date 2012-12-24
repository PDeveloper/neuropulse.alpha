#include <ac\es.h>
#include <OgreEntity.h>
#include <OgreSceneNode.h>

#pragma once
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

