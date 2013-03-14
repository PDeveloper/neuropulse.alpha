#include <ac\es.h>

#include <vector>
#include <NeuroPlayer.h>

#include <GameObjectFactory.h>

#include <GraphicSystem.h>
#include <AnimationSystem.h>
#include <OutputSystem.h>
#include <ReactionSystem.h>
#include <ConnectionDisplaySystem.h>
#include <PulseSystem.h>

#include <EventManager.h>

#include <NeuroWorldSettings.h>

#pragma once
namespace np
{

	class NeuroWorld
	{
	public:

		// Settings
		np::NeuroWorldSettings* settings;

		// OGRE
		Ogre::SceneManager* sceneManager;
		Ogre::Camera* camera;

		Ogre::RaySceneQuery* entityRayQuery;

		// Objects
		np::NeuroPlayer* player;
		std::vector<ac::es::EntityPtr> nodes;
		std::vector<ac::es::EntitySystem*> systems;

		np::GameObjectFactory* gameObjectFactory;

		// ES
		ac::es::Scene* esScene;
		// Systems
		np::GraphicSystem* graphicSystem;
		np::AnimationSystem* animationSystem;
		np::OutputSystem* outputSystem;
		np::ReactionSystem* reactionSystem;
		np::ConnectionDisplaySystem* connectionDisplaySystem;
		np::PulseSystem* pulseSystem;

		// Event system
		np::EventManager* eventManager;

		NeuroWorld( np::NeuroWorldSettings* settings);
		~NeuroWorld(void);

		void update( double timeSinceLastFrame);
		Ogre::Entity* getEntityUnderPoint( float x, float y);

	private:
		void cleanup(void);
		void addEntitySystem( ac::es::EntitySystem* system);
		void removeAllEntitySystems();
	};

}