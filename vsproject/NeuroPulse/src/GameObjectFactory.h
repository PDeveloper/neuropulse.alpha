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
	CONSTRUCT_MASK = 1 << 1
};

namespace np
{
	class GameObjectFactory
	{
	public:

		GameObjectFactory( Ogre::SceneManager* sceneManager, ac::es::Scene* scene);
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
		void killHubEntity( ac::es::EntityPtr e);

		ac::es::EntityPtr createConstructConnectionEntity( np::TransformComponent* target1, np::TransformComponent* target2 );
		void killConstructConnectionEntity( ac::es::EntityPtr e);

		void releasePulseEntity( ac::es::EntityPtr e);

	private:
		Ogre::SceneManager* sceneManager;
		ac::es::Scene* scene;

		std::stack<ac::es::EntityPtr> pulsePool;

		void generateMeshes(void);
		void setConstruct( ac::es::EntityPtr constructEntity, np::Construct* construct);
		void createResourceInput( ac::es::EntityPtr constructEntity, int slot);
		void createResourceOutput( ac::es::EntityPtr constructEntity, int slot);
	};
}