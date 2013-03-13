#include <ac\es.h>
#include <Ogre.h>

#include <string>
#include <queue>

#include <TransformComponent.h>

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
		ac::es::EntityPtr createConnectionEntity( np::TransformComponent* target1, np::TransformComponent* target2);
		ac::es::EntityPtr createPulseEntity( Ogre::Vector3& target1, Ogre::Vector3& target2);

		void releasePulseEntity( ac::es::EntityPtr e);
		void killPulseEntity( ac::es::EntityPtr e);

	private:
		Ogre::SceneManager* sceneManager;
		ac::es::Scene* scene;

		std::queue<ac::es::EntityPtr> pulsePool;

		void generateMeshes(void);
	};
}