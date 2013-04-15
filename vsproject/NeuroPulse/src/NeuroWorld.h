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
#include <PulseTransferSystem.h>
#include <HeatSystem.h>
#include "ConstructConnectionSystem.h"
#include <ConstructUpgradeSystem.h>

#include <EventManager.h>

#include <NeuroWorldSettings.h>

#pragma once
#include "ResourceTransferSystem.h"
#include "ConstructSystem.h"
#include "HubConstructionSystem.h"
#include "CameraComponent.h"
#include "CameraControlSystem.h"
namespace np
{

	class NeuroWorld
	{
	public:

		double timeSinceLastUpdate;

		// Settings
		np::NeuroWorldSettings* settings;

		// OGRE
		Ogre::SceneManager* sceneManager;
		Ogre::Camera* camera;

		Ogre::RaySceneQuery* entityRayQuery;

		// Objects
		np::NeuroPlayer* player;
		std::vector<ac::es::EntityPtr> nodes;
		std::vector<ac::es::EntityPtr> constructs;
		std::vector<ac::es::EntityPtr> constructConnections;
		std::vector<ac::es::EntitySystem*> systems;

		ac::es::EntityPtr cameraController;

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
		np::PulseTransferSystem* pulseTransferSystem;
		np::HeatSystem* heatSystem;
		np::ConstructConnectionSystem* constructConnectionSystem;

		np::ConstructSystem* constructSystem;
		np::ResourceTransferSystem* resourceTransferSystem;
		np::ConstructUpgradeSystem* constructUpgradeSystem;
		np::HubConstructionSystem* hubConstructionSystem;

		np::CameraControlSystem* cameraControlSystem;
		Ogre::Vector3 cameraOffset;
		Ogre::Quaternion defaultCameraView;

		// Event system
		np::EventManager* eventManager;

		NeuroWorld( np::NeuroWorldSettings* settings);
		~NeuroWorld(void);

		void update( double timeSinceLastFrame);
		Ogre::Entity* getEntityUnderPoint( float x, float y);

		Ogre::Entity* getNodeUnderPoint( float x, float y);
		Ogre::Entity* getConstructUnderPoint( float x, float y);
		Ogre::Entity* getConstructConnectorUnderPoint( float x, float y);
		Ogre::Entity* getNearestConstructConnectionFromPoint( float x, float y, double maxDistance = 4.0);
		std::pair<int,double> getNearestConnectionFromPoint( float x, float y, ac::es::EntityPtr node, double maxDistance = 4.0);

		Ogre::Vector3 getRayPlane( float x, float y, double altitude = 13.0);
		void movePulseGate( ac::es::EntityPtr pulseGate, int connection);

		bool isValid( ac::es::EntityPtr e1, ac::es::EntityPtr e2);
		bool isValidInputOutput( ac::es::EntityPtr input, ac::es::EntityPtr output);

		bool connect( ac::es::EntityPtr e1, ac::es::EntityPtr e2);
		bool connectInputOutput( ac::es::EntityPtr input, ac::es::EntityPtr output);
		bool disconnect( ac::es::EntityPtr e1, ac::es::EntityPtr e2);
		bool disconnectInputOutput( ac::es::EntityPtr input, ac::es::EntityPtr output);

		np::CameraComponent* getCameraController();
		np::TransformComponent* getCameraTransform();
	private:
		void cleanup(void);
		void addEntitySystem( ac::es::EntitySystem* system);
		void removeAllEntitySystems();
	};

}