#include <ac\es.h>
#include <OgreSceneManager.h>

#include <string>

#pragma once
class EntityFactory
{
public:
	EntityFactory( Ogre::SceneManager* sceneManager, ac::es::Scene* scene);
	~EntityFactory(void);

	ac::es::EntityPtr createNodeEntity( std::string name);
private:
	Ogre::SceneManager* sceneManager;
	ac::es::Scene* scene;

	void initNodeMesh(void);
};

