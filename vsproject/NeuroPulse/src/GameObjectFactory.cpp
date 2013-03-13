#include <GameObjectFactory.h>

#include <GraphicComponent.h>
#include <TransformComponent.h>
#include <AnimationComponent.h>
#include <ReactionComponent.h>
#include <OutputComponent.h>
#include <NodeComponent.h>
#include <ConnectionComponent.h>
#include <PulseComponent.h>

#include <TweenState.h>

#include <AdvancedOgreFramework.hpp>

#include <OgreProcedural\Procedural.h>

#define _USE_MATH_DEFINES
#include <math.h>

np::GameObjectFactory::GameObjectFactory( Ogre::SceneManager* sceneManager, ac::es::Scene* scene) :
	pulsePool()
{
	this->sceneManager = sceneManager;
	this->scene = scene;

	generateMeshes();
}

np::GameObjectFactory::~GameObjectFactory(void)
{

}

void np::GameObjectFactory::generateMeshes(void)
{
	/*Ogre::ManualObject* manual = sceneManager->createManualObject("nodeManualObject");

	int segments = 16;
	double innerRadius = 20.0;
	double outerRadius = 30.0;
	double yOffset = 20.0;

	manual->begin( "BaseWhiteNoLighting", Ogre::RenderOperation::OT_TRIANGLE_STRIP);
	{
		for ( int i = 0; i < segments; i++)
		{
			double rads = ( double(i) / double(segments)) * M_PI * 2.0;

			manual->position( outerRadius * std::cos( rads), 0.0, outerRadius * std::sin( rads));
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

	manual->convertToMesh( "NodeMesh");*/
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

	Procedural::TriangleBuffer tb;
	
	Procedural::CubicHermiteSpline2 outSpline = Procedural::CubicHermiteSpline2().addPoint( 8.0, 0.0).addPoint( 4.0, 4.0).addPoint( 17.0, 10.0).addPoint( 15.0, 14.0);
	Procedural::CubicHermiteSpline2 inSpline = Procedural::CubicHermiteSpline2().addPoint( 15.0, 14.0).addPoint( 3.0, 6.0).addPoint( 4.0, 0.0);

	Procedural::Shape outNodeSiding = outSpline.realizeShape();
	Procedural::Lathe().setShapeToExtrude( &outNodeSiding).addToTriangleBuffer( tb);
	Procedural::Shape inNodeSiding = inSpline.realizeShape();
	Procedural::Lathe().setShapeToExtrude( &inNodeSiding).addToTriangleBuffer( tb);

	Ogre::MeshPtr nodeMesh = tb.transformToMesh( "NodeMesh");
	nodeMesh->getSubMesh(0)->setMaterialName( "NodeMaterial");

	Procedural::Path path = Procedural::LinePath().betweenPoints(	Ogre::Vector3( 0.0, 0.0, -50.0),
		Ogre::Vector3( 0.0, 0.0, 50.0)).realizePath();
	
	Procedural::Shape circle = Procedural::CircleShape().setRadius( 2.0).setNumSeg( 10).realizeShape();
	Procedural::Track t = Procedural::Track(Procedural::Track::AM_RELATIVE_LINEIC).addKeyFrame( 0.0, 1.0).addKeyFrame( 0.5, 0.6).addKeyFrame( 1.0, 1.0);
	Ogre::MeshPtr connectionMesh = Procedural::Extruder().setExtrusionPath( &path).setScaleTrack( &t).setShapeToExtrude( &circle).realizeMesh( "ConnectionMesh");
	connectionMesh->getSubMesh(0)->setMaterialName( "ConnectionMaterial");

	Ogre::MeshPtr pulseMesh = Procedural::SphereGenerator().setRadius( 2.1).setUTile(.5f).realizeMesh("PulseMesh");
	pulseMesh->getSubMesh(0)->setMaterialName( "PulseMaterial");
}

ac::es::EntityPtr np::GameObjectFactory::createNodeEntity( double x, double y, double reactorOutput, double threshold)
{
	ac::es::EntityPtr e = scene->createEntity();
	
	//Need to fill in correct params:
	Ogre::Entity* entity = sceneManager->createEntity( "NodeMesh");
	entity->getUserObjectBindings().setUserAny( Ogre::String( "Entity"), Ogre::Any( e));

	entity->setQueryFlags( NODE_MASK);
	
	Ogre::Entity* entities[] = { entity};
	np::GraphicComponent* graphic = new np::GraphicComponent( entities, 1);
	np::TransformComponent* transform = new np::TransformComponent( x, 0.0, y);
	np::ReactionComponent* reactor = new np::ReactionComponent( reactorOutput);
	np::NodeComponent* node = new np::NodeComponent( threshold);
	np::OutputComponent* output = new np::OutputComponent();

	e->addComponent( graphic);
	e->addComponent( transform);
	e->addComponent( reactor);
	e->addComponent( node);
	e->addComponent( output);

	e->activate();

	return e;
}

ac::es::EntityPtr np::GameObjectFactory::createConnectionEntity( np::TransformComponent* target1, np::TransformComponent* target2)
{
	ac::es::EntityPtr e = scene->createEntity();

	Ogre::Entity* entity = sceneManager->createEntity( "ConnectionMesh");
	entity->setCastShadows( false);

	Ogre::Entity* entities[] = { entity};
	np::GraphicComponent* graphic = new np::GraphicComponent( entities, 1);
	np::ConnectionComponent* connection = new np::ConnectionComponent( target1, target2);
	
	e->addComponent( graphic);
	e->addComponent( connection);

	e->activate();

	return e;
}

ac::es::EntityPtr np::GameObjectFactory::createPulseEntity( Ogre::Vector3& target1, Ogre::Vector3& target2)
{
	ac::es::EntityPtr e;

	if ( pulsePool.empty())
	{
		e = scene->createEntity();

		Ogre::Entity* entity = sceneManager->createEntity( "PulseMesh");
		entity->setCastShadows( false);
		
		Ogre::Entity* entities[] = { entity};
		np::GraphicComponent* graphic = new np::GraphicComponent( entities, 1);
		np::TransformComponent* transform = new np::TransformComponent( target1.x, target1.y, target1.z);

		np::TweenState states[] = { np::TweenState( target1, 0.0), np::TweenState( target2, 0.7)};
		np::AnimationComponent* animation = new np::AnimationComponent( states, 2);
		animation->isLooping = false;

		np::PulseComponent* pulse = new np::PulseComponent();
		
		e->addComponent( graphic);
		e->addComponent( transform);
		e->addComponent( animation);
		e->addComponent( pulse);
	}
	else
	{
		e = pulsePool.front();
		pulsePool.pop();
		
		np::GraphicComponent* graphic		= e->getComponent<np::GraphicComponent>();
		np::TransformComponent* transform	= e->getComponent<np::TransformComponent>();
		np::AnimationComponent* animation	= e->getComponent<np::AnimationComponent>();

		transform->position = target1;
		animation->states.at(0).target = target1;
		animation->states.at(1).target = target2;

		graphic->node->attachObject( graphic->entity);
	}

	e->activate();

	return e;
}

void np::GameObjectFactory::releasePulseEntity( ac::es::EntityPtr e)
{
	np::GraphicComponent* graphics		= e->getComponent<np::GraphicComponent>();
	np::TransformComponent* transform	= e->getComponent<np::TransformComponent>();
	np::AnimationComponent* animation	= e->getComponent<np::AnimationComponent>();
	np::PulseComponent* pulse			= e->getComponent<np::PulseComponent>();
	
	for (std::list<Ogre::Entity*>::iterator it = graphics->entities.begin(); it != graphics->entities.end(); it++)
		graphics->node->detachObject( (*it));

	e->deactivate();
	
	pulsePool.push( e);
}

void np::GameObjectFactory::killPulseEntity( ac::es::EntityPtr e)
{
	np::GraphicComponent* graphics		= e->getComponent<np::GraphicComponent>();
	np::TransformComponent* transform	= e->getComponent<np::TransformComponent>();
	np::AnimationComponent* animation	= e->getComponent<np::AnimationComponent>();
	np::PulseComponent* pulse			= e->getComponent<np::PulseComponent>();

	for (std::list<Ogre::Entity*>::iterator it = graphics->entities.begin(); it != graphics->entities.end(); it++)
		graphics->node->detachObject( (*it));

	Ogre::SceneManager* sceneManager = graphics->node->getCreator();
	sceneManager->destroySceneNode( graphics->node);

	graphics->node = NULL;

	e->destroyComponent( graphics);
	e->destroyComponent( transform);
	e->destroyComponent( animation);
	e->destroyComponent( pulse);

	e->kill();
}