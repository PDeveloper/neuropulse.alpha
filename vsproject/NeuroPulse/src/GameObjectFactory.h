#include <ac\es.h>
#include <Ogre.h>

#include <string>
#include <queue>
#include <stack>

#include <TransformComponent.h>
#include <Construct.h>

#include <NeuroPlayer.h>

#pragma once

enum QueryFlags
{
	NODE_MASK = 1 << 0,
	CONSTRUCT_MASK = 1 << 1,
	CONSTRUCT_CONNECTOR_MASK = 1 << 2,
	CONSTRUCT_CONNECTION_MASK = 1 << 3
};

namespace np
{

	class NeuroWorld;

	class GameObjectFactory
	{
	public:

		GameObjectFactory( np::NeuroWorld* world);
		~GameObjectFactory(void);

		Ogre::Light* createLight( std::string name,
			Ogre::Light::LightTypes type = Ogre::Light::LT_DIRECTIONAL,
			Ogre::ColourValue diffuseColour = Ogre::ColourValue( 0.25, 0.25, 0.25),
			Ogre::ColourValue specularColour = Ogre::ColourValue( 0.25, 0.25, 0.25),
			Ogre::Vector3 direction = Ogre::Vector3( 0.5, -1, -1 ) );

		Ogre::Entity* createGround();

		ac::es::EntityPtr createNodeEntity( double x, double y, double reactorOutput, double threshold);
		void killNodeEntity( ac::es::EntityPtr e);

		ac::es::EntityPtr createConnectionEntity( np::TransformComponent* target1, np::TransformComponent* target2);
		void killConnectionEntity( ac::es::EntityPtr e);

		ac::es::EntityPtr createPulseEntity( Ogre::Vector3& target1, Ogre::Vector3& target2);
		void killPulseEntity( ac::es::EntityPtr e);

		ac::es::EntityPtr createConstructEntity( ac::es::EntityPtr hubEntity, Ogre::Degree degrees, Ogre::Real distance);
		void killConstructEntity( ac::es::EntityPtr e);

		void createHub( ac::es::EntityPtr nodeEntity, np::NeuroPlayer* player);
		void killHub( ac::es::EntityPtr nodeEntity);

		ac::es::EntityPtr createConstructConnectionEntity( ac::es::EntityPtr e1, ac::es::EntityPtr e2);
		void killConstructConnectionEntity( ac::es::EntityPtr e);

		ac::es::EntityPtr createPulseGate( int connection, double position, ac::es::EntityPtr nodeEntity, np::ResourceRequirement* requirement, bool isInput);
		void killPulseGate( ac::es::EntityPtr e);

		void releasePulseEntity( ac::es::EntityPtr e);
		void setConstruct( ac::es::EntityPtr constructEntity, np::Construct* construct);
		void removeConstruct( ac::es::EntityPtr constructEntity, np::Construct* construct);

		ac::es::EntityPtr createProxyHubEntity( ac::es::EntityPtr nodeEntity, np::NeuroPlayer* player);
		void killProxyHubEntity( ac::es::EntityPtr e);

		ac::es::EntityPtr createRawConstructConnectionEntity( const Ogre::Vector3& position1, const Ogre::Vector3& position2);
	private:

		np::NeuroWorld* world;
		Ogre::SceneManager* sceneManager;
		ac::es::Scene* scene;

		std::stack<ac::es::EntityPtr> pulsePool;

		void generateMeshes(void);
		ac::es::EntityPtr createResourceBud( ac::es::EntityPtr constructEntity, np::ResourceRequirement* requirement, bool isInput, int slot);
		void killResourceBud( ac::es::EntityPtr e);
	};
}