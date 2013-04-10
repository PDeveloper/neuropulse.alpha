#include "GraphicSystem.h"
#include "GraphicComponent.h"
#include "TransformComponent.h"
#include <Ogre.h>
#include <AdvancedOgreFramework.hpp>

#include <math.h>

np::GraphicSystem::GraphicSystem( Ogre::SceneManager* mSceneMgr) :
	ac::es::EntityProcessingSystem( ac::es::ComponentFilter::Requires<GraphicComponent>().requires<TransformComponent>())
{
	this->mSceneMgr = mSceneMgr;
}


np::GraphicSystem::~GraphicSystem(void)
{
}

void np::GraphicSystem::process( ac::es::EntityPtr e)
{
	GraphicComponent* graphic = e->getComponent<GraphicComponent>();
	TransformComponent* transform = e->getComponent<TransformComponent>();

	graphic->node->setPosition( transform->position);
	graphic->node->setOrientation( transform->rotation);
	graphic->node->setScale( transform->scale);

	if ( graphic->isDirty)
	{
		for (std::list<Ogre::MovableObject*>::iterator it = graphic->entities.begin(); it != graphic->entities.end(); it++)
			if ( (*it)->getParentSceneNode() == NULL)
			{
				graphic->node->attachObject( (*it));
			}
	}
}

void np::GraphicSystem::onAddedEntity( ac::es::EntityPtr e)
{
	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Entity has been added! :o");
	GraphicComponent* graphics = e->getComponent<GraphicComponent>();
	TransformComponent* transform = e->getComponent<TransformComponent>();
	
	//OgreFramework::getSingletonPtr()->m_pLog->logMessage(Ogre::StringConverter::toString(transform->position.x));
	//OgreFramework::getSingletonPtr()->m_pLog->logMessage(Ogre::StringConverter::toString(transform->position.y));
	//OgreFramework::getSingletonPtr()->m_pLog->logMessage(Ogre::StringConverter::toString(transform->position.z));

	if ( graphics->node == NULL)
	{
		Ogre::SceneNode* newNode;

		if ( graphics->parent != NULL && graphics->parent->node != NULL)
		{
			OgreFramework::getSingletonPtr()->m_pLog->logMessage( "Processing a child graphic");
			newNode = graphics->parent->node;
		}
		else
		{
			newNode = mSceneMgr->getRootSceneNode();
		}

		addChildren( newNode, e);
		graphics->isDirty = false;
	}
}

void np::GraphicSystem::addChildren( Ogre::SceneNode* parent, ac::es::EntityPtr child)
{
	np::GraphicComponent* graphic = child->getComponent<np::GraphicComponent>();
	np::TransformComponent* transform = child->getComponent<np::TransformComponent>();

	Ogre::SceneNode* newNode = parent->createChildSceneNode( transform->position, transform->rotation);

	graphic->node = newNode;

	for (std::list<Ogre::MovableObject*>::iterator it = graphic->entities.begin(); it != graphic->entities.end(); it++)
		newNode->attachObject( (*it));

	for (std::list<ac::es::EntityPtr>::iterator it = graphic->children.begin(); it != graphic->children.end(); it++)
	{
		addChildren( newNode, *it);
	}
}

void np::GraphicSystem::onRemovedEntity( ac::es::EntityPtr e)
{
	// Hm...how to remove an entity when it's graphics component is already gone...
}
