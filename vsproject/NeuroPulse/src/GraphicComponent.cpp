#include <GraphicComponent.h>

#include <AdvancedOgreFramework.hpp>

np::GraphicComponent::GraphicComponent( Ogre::Entity* entities[], int numEntities) :
	entities( entities, entities + numEntities ),
	children(),
	node(NULL)
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

		for (std::list<Ogre::Entity*>::iterator it = entities.begin(); it != entities.end(); it++)
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
	for (std::list<Ogre::Entity*>::iterator it = entities.begin(); it != entities.end(); it++)
	{
		if ( entity == (*it) && entity->getParentSceneNode() != NULL)
		{
			entity->getParentSceneNode()->detachObject( (*it)->getName());
			entities.remove( (*it));
		}
	}
}

void np::GraphicComponent::addChild( ac::es::EntityPtr e)
{
	children.push_back( e);
	np::GraphicComponent* graphic = e->getComponent<np::GraphicComponent>();
	graphic->parent = this;
}

void np::GraphicComponent::removeChild( ac::es::EntityPtr e)
{
	np::GraphicComponent* graphic = e->getComponent<np::GraphicComponent>();
	graphic->parent = NULL;
	children.remove( e);
}

void np::GraphicComponent::show()
{
	for (std::list<Ogre::Entity*>::iterator it = entities.begin(); it != entities.end(); it++)
		(*it)->setVisible( true);

	for (std::list<ac::es::EntityPtr>::iterator it = children.begin(); it != children.end(); it++)
	{
		ac::es::EntityPtr e = (*it);
		np::GraphicComponent* graphic = e->getComponent<np::GraphicComponent>();

		graphic->show();
	}
}

void np::GraphicComponent::hide()
{
	for (std::list<Ogre::Entity*>::iterator it = entities.begin(); it != entities.end(); it++)
		(*it)->setVisible( false);

	for (std::list<ac::es::EntityPtr>::iterator it = children.begin(); it != children.end(); it++)
	{
		ac::es::EntityPtr e = (*it);
		np::GraphicComponent* graphic = e->getComponent<np::GraphicComponent>();

		graphic->hide();
	}
}
