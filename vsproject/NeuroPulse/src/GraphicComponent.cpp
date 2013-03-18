#include <GraphicComponent.h>

#include <AdvancedOgreFramework.hpp>

np::GraphicComponent::GraphicComponent( Ogre::MovableObject* entities[], int numEntities) :
	entities( entities, entities + numEntities ),
	node( NULL)
{
	isDirty = false;

	parent = NULL;
}

np::GraphicComponent::~GraphicComponent(void)
{
	OgreFramework::getSingletonPtr()->m_pLog->logMessage( "graphic component destroyed");

	if ( node != NULL)
	{
		Ogre::SceneManager* sceneManager = node->getCreator();

		for (std::list<Ogre::MovableObject*>::iterator it = entities.begin(); it != entities.end(); it++)
		{
			node->detachObject( (*it)->getName());
			sceneManager->destroyEntity( (*it)->getName());
		}

		sceneManager->destroySceneNode( node);
	}
}

void np::GraphicComponent::addEntity( Ogre::Entity* entity)
{
	isDirty = true;
	entities.push_back( entity);
}

void np::GraphicComponent::removeEntity( Ogre::Entity* entity)
{
	for (std::list<Ogre::MovableObject*>::iterator it = entities.begin(); it != entities.end(); it++)
	{
		if ( entity == (*it) && entity->getParentSceneNode() != NULL)
		{
			entity->getParentSceneNode()->detachObject( (*it)->getName());
			entities.remove( (*it));
		}
	}
}

void np::GraphicComponent::addChild( np::GraphicComponent* graphic )
{
	children.push_back( graphic);
	graphic->parent = this;
}

void np::GraphicComponent::removeChild( np::GraphicComponent* graphic )
{
	children.remove( graphic);
	graphic->parent = NULL;
}
