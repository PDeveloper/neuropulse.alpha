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
}

void np::GraphicSystem::onAddedEntity( ac::es::EntityPtr e)
{
	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Entity has been added! :o");
	GraphicComponent* graphics = e->getComponent<GraphicComponent>();
	TransformComponent* transform = e->getComponent<TransformComponent>();
	
	OgreFramework::getSingletonPtr()->m_pLog->logMessage(Ogre::StringConverter::toString(transform->position.x));
	OgreFramework::getSingletonPtr()->m_pLog->logMessage(Ogre::StringConverter::toString(transform->position.y));
	OgreFramework::getSingletonPtr()->m_pLog->logMessage(Ogre::StringConverter::toString(transform->position.z));

	Ogre::SceneNode* newNode = mSceneMgr->getRootSceneNode()->createChildSceneNode( transform->position, transform->rotation);

	newNode->attachObject( graphics->entity);

	graphics->node = newNode;
}

void np::GraphicSystem::onRemovedEntity( ac::es::EntityPtr e)
{
	// Hm...how to remove an entity when it's graphics component is already gone...
}