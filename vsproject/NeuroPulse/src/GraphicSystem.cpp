#include "GraphicSystem.h"
#include "GraphicComponent.h"
#include "TransformComponent.h"
#include <Ogre.h>
#include <AdvancedOgreFramework.hpp>

np::GraphicSystem::GraphicSystem(void) :
	ac::es::EntityProcessingSystem( ac::es::ComponentFilter::Requires<GraphicComponent>().requires<TransformComponent>())
{
	mSceneMgr = OgreFramework::getSingletonPtr()->m_pRoot->createSceneManager( Ogre::ST_GENERIC, "GraphicSystemMgr");
}


np::GraphicSystem::~GraphicSystem(void)
{
}

void np::GraphicSystem::onAddedEntity( ac::es::EntityPtr e)
{
	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Entity has been added! :o");
	GraphicComponent* graphics = e->getComponent<GraphicComponent>();
	TransformComponent* transform = e->getComponent<TransformComponent>();

	Ogre::String nodeName =  graphics->entity->getName() + "Node";
	
	OgreFramework::getSingletonPtr()->m_pLog->logMessage(Ogre::StringConverter::toString(transform->position.x));
	OgreFramework::getSingletonPtr()->m_pLog->logMessage(Ogre::StringConverter::toString(transform->position.y));
	OgreFramework::getSingletonPtr()->m_pLog->logMessage(Ogre::StringConverter::toString(transform->position.z));

	Ogre::SceneNode* newNode = mSceneMgr->getRootSceneNode()->createChildSceneNode( nodeName, transform->position, transform->rotation);

	newNode->attachObject( graphics->entity);

	graphics->node = newNode;
}

void np::GraphicSystem::onRemovedEntity( ac::es::EntityPtr e)
{
	// Hm...how to remove an entity when it's graphics component is already gone...
}

void np::GraphicSystem::process( ac::es::Entity& e)
{
	GraphicComponent* graphic = e.getComponent<GraphicComponent>();
	TransformComponent* transform = e.getComponent<TransformComponent>();
	
	transform->position.x += 1.0;

	graphic->node->setPosition( transform->position);
	graphic->node->setOrientation( transform->rotation);
}