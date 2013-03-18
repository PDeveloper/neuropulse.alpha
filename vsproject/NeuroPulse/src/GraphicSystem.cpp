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
			newNode = graphics->parent->node->createChildSceneNode( transform->position, transform->rotation);
		}
		else
		{
			newNode = mSceneMgr->getRootSceneNode()->createChildSceneNode( transform->position, transform->rotation);
		}

		for (std::list<Ogre::MovableObject*>::iterator it = graphics->entities.begin(); it != graphics->entities.end(); it++)
			newNode->attachObject( (*it));
		
		for (std::list<np::GraphicComponent*>::iterator it = graphics->children.begin(); it != graphics->children.end(); it++)
		{
			addChildren( graphics, *it);
		}

		graphics->node = newNode;
		graphics->isDirty = false;
	}
}

void np::GraphicSystem::addChildren( np::GraphicComponent* parent, np::GraphicComponent* child )
{
	Ogre::SceneNode* newNode = parent->node->createChildSceneNode();

	child->node = newNode;

	for (std::list<Ogre::MovableObject*>::iterator it = child->entities.begin(); it != child->entities.end(); it++)
		newNode->attachObject( (*it));

	for (std::list<np::GraphicComponent*>::iterator it = child->children.begin(); it != child->children.end(); it++)
	{
		addChildren( child, *it);
	}
}

void np::GraphicSystem::onRemovedEntity( ac::es::EntityPtr e)
{
	// Hm...how to remove an entity when it's graphics component is already gone...
}
