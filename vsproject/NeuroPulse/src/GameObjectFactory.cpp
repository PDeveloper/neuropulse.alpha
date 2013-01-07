#include <GameObjectFactory.h>

#include <GraphicComponent.h>
#include <TransformComponent.h>
#include <AnimationComponent.h>
#include <ReactionComponent.h>
#include <OutputComponent.h>
#include <NodeComponent.h>

#include <TweenState.h>

#include <AdvancedOgreFramework.hpp>

#define _USE_MATH_DEFINES
#include <math.h>

np::GameObjectFactory::GameObjectFactory( Ogre::SceneManager* sceneManager, ac::es::Scene* scene)
{
	this->sceneManager = sceneManager;
	this->scene = scene;

	initNodeMesh();
}

np::GameObjectFactory::~GameObjectFactory(void)
{
}

void np::GameObjectFactory::initNodeMesh(void)
{
    Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
 
    Ogre::MeshManager::getSingleton().createPlane("NODE_TEST", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        plane, 40, 40, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);

	Ogre::ManualObject* manual = sceneManager->createManualObject("nodeManualObject");

	int segments = 16;
	double innerRadius = 20.0;
	double outerRadius = 30.0;
	double yOffset = 10.0;

	manual->begin( "BaseWhiteNoLighting", Ogre::RenderOperation::OT_TRIANGLE_STRIP);
	{
		for ( int i = 0; i < segments; i++)
		{
			double rads = ( double(i) / double(segments)) * M_PI * 2.0;

			manual->position( outerRadius * std::cos( rads), -yOffset, outerRadius * std::sin( rads));
			manual->colour( Ogre::ColourValue(0.4f,0.0f,0.0f,1.0f));

			manual->position( innerRadius * std::cos( rads), yOffset, innerRadius * std::sin( rads));
			manual->colour( Ogre::ColourValue(0.4f,0.0f,0.0f,1.0f));

			manual->index( i << 1);
			manual->index(( i << 1) + 1);
		}

		manual->index(0);
		manual->index(1);
	}
	manual->end();
	manual->begin( "BaseWhiteNoLighting", Ogre::RenderOperation::OT_TRIANGLE_FAN);
	{
		manual->position( 0.0, yOffset * 0.9, 0.0);
		manual->colour( Ogre::ColourValue(0.0f,0.0f,1.0f,1.0f));

		manual->index(0);

		for ( int i = 0; i < segments; i++)
		{
			double rads = ( double(i) / double(segments)) * M_PI * 2.0;

			manual->position( innerRadius * std::cos( -rads), yOffset, innerRadius * std::sin( -rads));
			manual->colour( Ogre::ColourValue(0.0f,0.0f,0.6f,1.0f));

			manual->index( i + 1);
		}

		manual->index(1);
	}
	manual->end();

	manual->convertToMesh( "NodeMesh");
	/*
	float lSize = 0.7f;
	manual->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_TRIANGLE_LIST);
	{
		float cp = 1.0f * lSize ;
		float cm = -1.0f * lSize;
 
		manual->position(cm, cp, cm);// a vertex
		manual->colour(Ogre::ColourValue(0.0f,1.0f,0.0f,1.0f));
		manual->position(cp, cp, cm);// a vertex
		manual->colour(Ogre::ColourValue(1.0f,1.0f,0.0f,1.0f));
		manual->position(cp, cm, cm);// a vertex
		manual->colour(Ogre::ColourValue(1.0f,0.0f,0.0f,1.0f));
		manual->position(cm, cm, cm);// a vertex
		manual->colour(Ogre::ColourValue(0.0f,0.0f,0.0f,1.0f));
		
		manual->position(cm, cp, cp);// a vertex
		manual->colour(Ogre::ColourValue(0.0f,1.0f,1.0f,1.0f));
		manual->position(cp, cp, cp);// a vertex
		manual->colour(Ogre::ColourValue(1.0f,1.0f,1.0f,1.0f));
		manual->position(cp, cm, cp);// a vertex
		manual->colour(Ogre::ColourValue(1.0f,0.0f,1.0f,1.0f));
		manual->position(cm, cm, cp);// a vertex
		manual->colour(Ogre::ColourValue(0.0f,0.0f,1.0f,1.0f));

		manual->triangle(0,1,2);
		manual->triangle(2,3,0);
		manual->triangle(4,6,5);
		manual->triangle(6,4,7);

		manual->triangle(0,4,5);
		manual->triangle(5,1,0);
		manual->triangle(2,6,7);
		manual->triangle(7,3,2);

		manual->triangle(0,7,4);
		manual->triangle(7,0,3);
		manual->triangle(1,5,6);
		manual->triangle(6,2,1);			
	}
	manual->end();

	manual->convertToMesh( "Cube");
	*/
}

ac::es::EntityPtr np::GameObjectFactory::createNodeEntity( double x, double y, double output, double threshold)
{
	ac::es::EntityPtr e = scene->createEntity();
	
	//Need to fill in correct params:
	Ogre::Entity* entity = sceneManager->createEntity( "NodeMesh");

	np::GraphicComponent* graphic = new np::GraphicComponent( entity);
	np::TransformComponent* transform = new np::TransformComponent( x, 0.0, y);
	np::ReactionComponent* reactor = new np::ReactionComponent( output);
	np::NodeComponent* node = new np::NodeComponent( threshold);
	np::OutputComponent* output = new np::OutputComponent();

	e->addComponent( graphic);
	e->addComponent( transform);

	e->activate();

	return e;
}