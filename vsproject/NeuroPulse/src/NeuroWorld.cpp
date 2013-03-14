#include "NeuroWorld.h"
#include "AdvancedOgreFramework.hpp"
#include <Ogre.h>

np::NeuroWorld::NeuroWorld( np::NeuroWorldSettings* settings) :
	sceneManager( OgreFramework::getSingletonPtr()->m_pRoot->createSceneManager( Ogre::ST_GENERIC, "NeuroWorldSceneMgr")),
	settings( settings),
	nodes(),
	systems()
{
	sceneManager->setAmbientLight( Ogre::ColourValue(0.4f, 0.4f, 0.4f));
	sceneManager->setShadowTechnique( Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

	camera = sceneManager->createCamera("NeuroWorldCamera");
	camera->setPosition( Ogre::Vector3(5, 420, 60));
	camera->lookAt( Ogre::Vector3(5, 20, -60));
	camera->setNearClipDistance(5);
	camera->setAspectRatio( Ogre::Real(OgreFramework::getSingletonPtr()->m_pViewport->getActualWidth()) /
		Ogre::Real( OgreFramework::getSingletonPtr()->m_pViewport->getActualHeight()));
	OgreFramework::getSingletonPtr()->m_pViewport->setCamera( camera);

	entityRayQuery = sceneManager->createRayQuery( Ogre::Ray());

	esScene = new ac::es::Scene();
	gameObjectFactory = new np::GameObjectFactory( sceneManager, esScene);

	eventManager = new np::EventManager();

	/* init systems and shit */
	reactionSystem = new np::ReactionSystem();
	outputSystem = new np::OutputSystem( eventManager, settings);
	animationSystem = new np::AnimationSystem();
	graphicSystem = new np::GraphicSystem( sceneManager);
	connectionDisplaySystem = new np::ConnectionDisplaySystem( sceneManager);
	pulseSystem = new np::PulseSystem( gameObjectFactory, eventManager);

	addEntitySystem( reactionSystem);
	addEntitySystem( outputSystem);

	addEntitySystem( animationSystem);

	addEntitySystem( graphicSystem);
	addEntitySystem( connectionDisplaySystem);

	addEntitySystem( pulseSystem);
}

np::NeuroWorld::~NeuroWorld(void)
{
	cleanup();
}

void np::NeuroWorld::update( double timeSinceLastFrame )
{
	reactionSystem->setDeltaTime( timeSinceLastFrame);
	outputSystem->globalTick( timeSinceLastFrame);

	esScene->update();

	eventManager->refresh();
}

Ogre::Entity* np::NeuroWorld::getEntityUnderPoint( float x, float y)
{
	Ogre::Ray mouseRay = camera->getCameraToViewportRay( x, y);
	entityRayQuery->setRay( mouseRay);
	entityRayQuery->setSortByDistance( true);
	entityRayQuery->setQueryMask( NODE_MASK);

	Ogre::RaySceneQueryResult &result = entityRayQuery->execute();
	Ogre::RaySceneQueryResult::iterator itr;

	for(itr = result.begin(); itr != result.end(); itr++)
	{
		if(itr->movable)
		{
			return sceneManager->getEntity( itr->movable->getName());
		}
	}

	return NULL;
}

void np::NeuroWorld::cleanup( void )
{
	removeAllEntitySystems();

	delete esScene;

	sceneManager->destroyCamera( camera);
	sceneManager->destroyQuery( entityRayQuery);

	if( sceneManager)
		OgreFramework::getSingletonPtr()->m_pRoot->destroySceneManager( sceneManager);
}

void np::NeuroWorld::addEntitySystem( ac::es::EntitySystem* system )
{
	esScene->insertEntitySystem( system);
	systems.push_back( system);
}

void np::NeuroWorld::removeAllEntitySystems()
{
	for ( int i = 0; i < systems.size(); i++) esScene->removeEntitySystem( systems[i]);
}