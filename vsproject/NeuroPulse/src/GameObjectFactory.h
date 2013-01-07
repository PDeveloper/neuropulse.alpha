#include <ac\es.h>
#include <Ogre.h>

#include <string>

#pragma once
namespace np
{
	class GameObjectFactory
	{
	public:
		GameObjectFactory( Ogre::SceneManager* sceneManager, ac::es::Scene* scene);
		~GameObjectFactory(void);

		ac::es::EntityPtr createNodeEntity( std::string name);
		ac::es::EntityPtr createPulseEntity( std::string name);
	private:
		Ogre::SceneManager* sceneManager;
		ac::es::Scene* scene;

		void initNodeMesh(void);
	};
}