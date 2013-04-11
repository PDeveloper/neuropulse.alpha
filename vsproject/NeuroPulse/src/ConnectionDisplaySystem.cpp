#include "ConnectionDisplaySystem.h"

#include <ConnectionComponent.h>
#include <GraphicComponent.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include <AdvancedOgreFramework.hpp>
#include <Ogre.h>

np::ConnectionDisplaySystem::ConnectionDisplaySystem( Ogre::SceneManager* mSceneMgr) :
	ac::es::EntityProcessingSystem( ac::es::ComponentFilter::Requires<np::ConnectionComponent>().requires<np::GraphicComponent>())
{
	this->mSceneMgr = mSceneMgr;
}


np::ConnectionDisplaySystem::~ConnectionDisplaySystem(void)
{
}

void np::ConnectionDisplaySystem::process( ac::es::EntityPtr e)
{
	np::ConnectionComponent* connection = e->getComponent<np::ConnectionComponent>();
	np::GraphicComponent* graphics = e->getComponent<np::GraphicComponent>();
}

void np::ConnectionDisplaySystem::onAddedEntity( ac::es::EntityPtr e)
{
	np::ConnectionComponent* connection = e->getComponent<np::ConnectionComponent>();
	np::GraphicComponent* graphics = e->getComponent<np::GraphicComponent>();
	
	//OgreFramework::getSingletonPtr()->m_pLog->logMessage( "Connection to be displayed!");
	double mx = ( connection->target1->position.x + connection->target2->position.x) * 0.5;
	//OgreFramework::getSingletonPtr()->m_pLog->logMessage( Ogre::StringConverter::toString( (Ogre::Real)mx));
	double mz = ( connection->target1->position.z + connection->target2->position.z) * 0.5;
	//OgreFramework::getSingletonPtr()->m_pLog->logMessage( Ogre::StringConverter::toString( (Ogre::Real)mz));

	double dx = connection->target2->position.x - connection->target1->position.x;
	double dz = connection->target2->position.z - connection->target1->position.z;
	double d = std::sqrt( dx * dx + dz * dz) / 100.0;

	Ogre::Vector3 position( mx, 0.0, mz);

	double rads = std::atan2( dx, dz);
	Ogre::Quaternion rotation( Ogre::Radian( rads), Ogre::Vector3::UNIT_Y);
	Ogre::SceneNode* newNode = mSceneMgr->getRootSceneNode()->createChildSceneNode( position, rotation);
	newNode->setScale( 1.0, 1.0, d);

	for (std::list<Ogre::Entity*>::iterator it = graphics->entities.begin(); it != graphics->entities.end(); it++)
		newNode->attachObject( (*it));

	graphics->node = newNode;
}

void np::ConnectionDisplaySystem::onRemovedEntity( ac::es::EntityPtr e)
{
	// Hm...how to remove an entity when it's graphics component is already gone...
}