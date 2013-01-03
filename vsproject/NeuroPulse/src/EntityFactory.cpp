#include "EntityFactory.h"
#include "GraphicComponent.h"

#include <OgreEntity.h>
#include <OgreManualObject.h>
#include <OgreRenderOperation.h>

#define _USE_MATH_DEFINES
#include <math.h>


EntityFactory::EntityFactory( Ogre::SceneManager* sceneManager, ac::es::Scene* scene)
{
	this->sceneManager = sceneManager;
	this->scene = scene;
}


EntityFactory::~EntityFactory(void)
{
}


void EntityFactory::initNodeMesh(void)
{
	Ogre::ManualObject* manual = sceneManager->createManualObject("manual");
	manual->begin( "BaseWhiteNoLighting", Ogre::RenderOperation::OT_TRIANGLE_STRIP);

	int segments = 16;
	for ( int i = 0; i < segments; i++)
	{
		double rads = ( i / segments) * M_PI * 2.0;
		manual->position( 100.0 * std::cos( rads), 100.0 * std::sin( rads), -30);
		manual->position( 60.0 * std::cos( rads), 60.0 * std::sin( rads), 30);

		manual->index(0);
		manual->index(1);
	}

	manual->index(0);
	
	manual->end();

	manual->convertToMesh( "NodeMesh", "General");
}

ac::es::EntityPtr EntityFactory::createNodeEntity( std::string name)
{
	ac::es::EntityPtr e = scene->createEntity();
	
	//Need to fill in correct params:
	Ogre::Entity* entity = sceneManager->createEntity( name, "NodeMesh");

	GraphicComponent* graphic = new GraphicComponent( entity);

	e->addComponent( graphic);

	e->activate();

	return e;
}
