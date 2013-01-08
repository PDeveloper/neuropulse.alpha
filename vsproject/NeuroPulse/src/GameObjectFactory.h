#include <ac\es.h>
#include <Ogre.h>

#include <string>

#include <TransformComponent.h>

#pragma once
namespace np
{
	class GameObjectFactory
	{
	public:
		GameObjectFactory( Ogre::SceneManager* sceneManager, ac::es::Scene* scene);
		~GameObjectFactory(void);

		ac::es::EntityPtr createNodeEntity( double x, double y, double reactorOutput, double threshold);
		ac::es::EntityPtr createConnectionEntity( np::TransformComponent* target1, np::TransformComponent* target2);
		ac::es::EntityPtr createPulseEntity();
	private:
		Ogre::SceneManager* sceneManager;
		ac::es::Scene* scene;

		void generateMeshes(void);
	};
}