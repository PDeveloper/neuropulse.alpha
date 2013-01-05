#include <GameObjectFactory.h>
#include <GraphicComponent.h>
#include <TransformComponent.h>

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
	manual->begin( "BaseWhiteNoLighting", Ogre::RenderOperation::OT_TRIANGLE_STRIP);

	int segments = 16;
	for ( int i = 0; i < segments; i++)
	{
		double rads = ( i / segments) * M_PI * 2.0;

		manual->position( 100.0 * std::cos( rads), 100.0 * std::sin( rads), -30);
		manual->colour(Ogre::ColourValue(1.0f,0.0f,0.0f,1.0f));

		manual->position( 60.0 * std::cos( rads), 60.0 * std::sin( rads), 30);
		manual->colour(Ogre::ColourValue(1.0f,0.0f,0.0f,1.0f));

		manual->index( i << 1);
		manual->index(( i << 1) + 1);
	}

	manual->index(0);
	
	manual->end();

	manual->convertToMesh( "NodeMesh", "General");
}

ac::es::EntityPtr np::GameObjectFactory::createNodeEntity( std::string name)
{
	ac::es::EntityPtr e = scene->createEntity();
	
	//Need to fill in correct params:
	Ogre::Entity* entity = sceneManager->createEntity( name, "NODE_TEST");

	GraphicComponent* graphic = new GraphicComponent( entity);
	TransformComponent* transform = new TransformComponent( 0.0, 0.0, 0.0);
	//transform->position.x = 0;
	transform->position.y = 40;
	//transform->position.z = 0;

	e->addComponent( graphic);
	e->addComponent( transform);

	e->activate();

	return e;
}