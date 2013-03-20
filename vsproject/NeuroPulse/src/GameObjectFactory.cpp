#include <GameObjectFactory.h>

#include <GraphicComponent.h>
#include <TransformComponent.h>
#include <AnimationComponent.h>
#include <ReactionComponent.h>
#include <OutputComponent.h>
#include <NodeComponent.h>
#include <ConnectionComponent.h>
#include <PulseComponent.h>
#include <ConstructComponent.h>
#include <HubComponent.h>
#include <BufferComponent.h>

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

	Ogre::MovableObject::setDefaultQueryFlags(0);

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

	///////// NODE MESH
	Procedural::TriangleBuffer tb;
	
	Procedural::CubicHermiteSpline2 outSpline = Procedural::CubicHermiteSpline2().addPoint( 14.0, 0.0).addPoint( 9.0, 4.0).addPoint( 7.0, 6.0);
	Procedural::CubicHermiteSpline2 inSpline = Procedural::CubicHermiteSpline2().addPoint( 7.0, 6.0).addPoint( 4.0, 2.0).addPoint( 2.0, 0.0);

	Procedural::Shape outNodeSiding = outSpline.realizeShape();
	Procedural::Shape inNodeSiding = inSpline.realizeShape().appendShape( outNodeSiding);

	Ogre::MeshPtr nodeMesh = Procedural::Lathe().setShapeToExtrude( &inNodeSiding).realizeMesh( "NodeMesh");
	nodeMesh->getSubMesh(0)->setMaterialName( "NodeMaterial");

	///////// CONNECTION MESH
	Procedural::Path path = Procedural::LinePath().betweenPoints(	Ogre::Vector3( 0.0, 0.0, -50.0),
		Ogre::Vector3( 0.0, 0.0, 50.0)).realizePath();
	
	Procedural::Shape circle = Procedural::CircleShape().setRadius( 2.0).setNumSeg( 10).realizeShape();
	Procedural::Track t = Procedural::Track(Procedural::Track::AM_RELATIVE_LINEIC).addKeyFrame( 0.0, 1.0).addKeyFrame( 0.5, 0.6).addKeyFrame( 1.0, 1.0);
	Ogre::MeshPtr connectionMesh = Procedural::Extruder().setExtrusionPath( &path).setScaleTrack( &t).setShapeToExtrude( &circle).realizeMesh( "ConnectionMesh");
	connectionMesh->getSubMesh(0)->setMaterialName( "ConnectionMaterial");

	///////// PULSE MESH
	Ogre::MeshPtr pulseMesh = Procedural::SphereGenerator().setRadius( 2.1).setUTile(.5f).realizeMesh("PulseMesh");
	pulseMesh->getSubMesh(0)->setMaterialName( "PulseMaterial");

	///////// RESOURCE BUD MESH
	Ogre::MeshPtr resMesh = Procedural::SphereGenerator().setRadius( 1.0).setUTile(.5f).realizeMesh("ResourceBudMesh");
	resMesh->getSubMesh(0)->setMaterialName( "ResourceBudMaterial");

	///////// GROUND MESH
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshPtr groundMesh = Ogre::MeshManager::getSingleton().createPlane( "GroundMesh", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);

	groundMesh->getSubMesh(0)->setMaterialName( "GroundMaterial");

	///////// HUB MESH

	Procedural::Shape hubShape = Procedural::RectangleShape().setHeight( 0.5).setWidth( 5.0).realizeShape();
	hubShape.translate( 10.0, 12.0);

	Ogre::MeshPtr hubMesh = Procedural::Lathe().setShapeToExtrude( &hubShape).realizeMesh( "HubMesh");
	hubMesh->getSubMesh(0)->setMaterialName( "HubMaterial");

	/*
	Procedural::Path hubPath = Procedural::LinePath().betweenPoints( Ogre::Vector3( 0.0, 15.0, 0.0),
		Ogre::Vector3( 0.0, 15.2, 0.0)).realizePath();

	Procedural::Shape hubCircle = Procedural::CircleShape().setRadius( 20.0).setNumSeg( 10).realizeShape();
	Ogre::MeshPtr hubMesh = Procedural::Extruder().setExtrusionPath( &hubPath).setShapeToExtrude( &hubCircle).realizeMesh( "HubMesh");
	hubMesh->getSubMesh(0)->setMaterialName( "HubMaterial");
	*/

	///////// CONSTRUCT MESH
	Procedural::Path constructPath = Procedural::LinePath().betweenPoints( Ogre::Vector3( 0.0, 12.0, 0.0),
		Ogre::Vector3( 0.0, 13.0, 0.0)).realizePath();

	Procedural::Shape square = Procedural::RectangleShape().setWidth( 16.0).setHeight( 16.0).realizeShape();//Procedural::Shape().addPoint( 0.0, -10.0).addPoint( -10.0, -9.0).addPoint( -8.0, 10.0).addPoint( 0.0, 10.0).reflect( Ogre::Vector2( 1.0, 0.0));
		//
	Ogre::MeshPtr constructMesh = Procedural::Extruder().setExtrusionPath( &constructPath).setShapeToExtrude( &square).realizeMesh( "ConstructMesh");
	constructMesh->getSubMesh(0)->setMaterialName( "ConstructMaterial");
}

Ogre::Light* np::GameObjectFactory::createLight( std::string name,
												Ogre::Light::LightTypes type,
												Ogre::ColourValue diffuseColour,
												Ogre::ColourValue specularColour,
												Ogre::Vector3 direction)
{
	Ogre::Light* directionalLight = sceneManager->createLight( name);

	directionalLight->setType( type);

	directionalLight->setDiffuseColour( diffuseColour);
	directionalLight->setSpecularColour( specularColour);

	directionalLight->setDirection( direction);

	return directionalLight;
}

Ogre::Entity* np::GameObjectFactory::createGround()
{
	Ogre::Entity* entGround = sceneManager->createEntity( "GroundMesh");
	entGround->setCastShadows( false);

	sceneManager->getRootSceneNode()->createChildSceneNode()->attachObject( entGround);

	return entGround;
}

ac::es::EntityPtr np::GameObjectFactory::createNodeEntity( double x, double y, double reactorOutput, double threshold)
{
	ac::es::EntityPtr e = scene->createEntity();
	
	//Need to fill in correct params:
	Ogre::Entity* entity = sceneManager->createEntity( "NodeMesh");
	entity->getUserObjectBindings().setUserAny( "Entity", Ogre::Any( e));
	entity->setQueryFlags( NODE_MASK);
	
	Ogre::MovableObject* entities[] = { entity};

	np::GraphicComponent* graphic = new np::GraphicComponent( entities, 1);
	np::TransformComponent* transform = new np::TransformComponent( x, 0.0, y);
	np::ReactionComponent* reactor = new np::ReactionComponent( reactorOutput);
	np::NodeComponent* node = new np::NodeComponent( threshold);
	np::OutputComponent* output = new np::OutputComponent();
	np::BufferComponent* buffer = new np::BufferComponent( np::ResourceRequirement::ANY);

	e->addComponent( graphic);
	e->addComponent( transform);
	e->addComponent( reactor);
	e->addComponent( node);
	e->addComponent( output);
	e->addComponent( buffer);

	e->activate();

	return e;
}

void np::GameObjectFactory::killNodeEntity( ac::es::EntityPtr e)
{
	np::GraphicComponent* graphics		= e->getComponent<np::GraphicComponent>();
	np::TransformComponent* transform	= e->getComponent<np::TransformComponent>();
	np::ReactionComponent* reactor		= e->getComponent<np::ReactionComponent>();
	np::NodeComponent* node				= e->getComponent<np::NodeComponent>();
	np::OutputComponent* output			= e->getComponent<np::OutputComponent>();
	np::HubComponent* hub				= e->getComponent<np::HubComponent>();
	np::BufferComponent* buffer			= e->getComponent<np::BufferComponent>();

	e->destroyComponent( graphics);
	e->destroyComponent( transform);
	e->destroyComponent( node);
	e->destroyComponent( reactor);
	e->destroyComponent( output);
	e->destroyComponent( buffer);
	if ( hub != NULL) e->destroyComponent( hub);

	e->kill();
}

ac::es::EntityPtr np::GameObjectFactory::createConnectionEntity( np::TransformComponent* target1, np::TransformComponent* target2)
{
	ac::es::EntityPtr e = scene->createEntity();

	Ogre::Entity* entity = sceneManager->createEntity( "ConnectionMesh");
	entity->setCastShadows( false);

	Ogre::MovableObject* entities[] = { entity};
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

		OgreFramework::getSingletonPtr()->m_pLog->logMessage( "New Pulse Entity created");

		Ogre::Entity* entity = sceneManager->createEntity( "PulseMesh");
		entity->setCastShadows( false);
		
		Ogre::MovableObject* entities[] = { entity};
		np::GraphicComponent* graphic = new np::GraphicComponent( entities, 1);
		np::TransformComponent* transform = new np::TransformComponent( target1.x, target1.y, target1.z);

		np::TweenState states[] = { np::TweenState( target1, 0.0), np::TweenState( target2, 0.4)};
		np::AnimationComponent* animation = new np::AnimationComponent( states, 2);
		animation->isLooping = false;

		np::PulseComponent* pulse = new np::PulseComponent();

		np::BufferComponent* buffer = new np::BufferComponent( np::ResourceRequirement::ANY);
		
		e->addComponent( graphic);
		e->addComponent( transform);
		e->addComponent( animation);
		e->addComponent( pulse);
		e->addComponent( buffer);
	}
	else
	{
		e = pulsePool.top();
		pulsePool.pop();
		
		np::GraphicComponent* graphic		= e->getComponent<np::GraphicComponent>();
		np::TransformComponent* transform	= e->getComponent<np::TransformComponent>();
		np::AnimationComponent* animation	= e->getComponent<np::AnimationComponent>();
		np::BufferComponent* buffer			= e->getComponent<np::BufferComponent>();

		buffer->clear();

		transform->position = target1;

		animation->stop();
		animation->play();
		animation->states.at(0).target = target1;
		animation->states.at(1).target = target2;

		std::list<Ogre::MovableObject*>::iterator it;
		for ( it = graphic->entities.begin(); it != graphic->entities.end(); ++it)
			(*it)->setVisible( true);
	}

	e->activate();

	return e;
}

void np::GameObjectFactory::killPulseEntity( ac::es::EntityPtr e)
{
	np::GraphicComponent* graphics		= e->getComponent<np::GraphicComponent>();
	np::TransformComponent* transform	= e->getComponent<np::TransformComponent>();
	np::AnimationComponent* animation	= e->getComponent<np::AnimationComponent>();
	np::PulseComponent* pulse			= e->getComponent<np::PulseComponent>();
	np::BufferComponent* buffer			= e->getComponent<np::BufferComponent>();

	e->destroyComponent( graphics);
	e->destroyComponent( transform);
	e->destroyComponent( animation);
	e->destroyComponent( pulse);
	e->destroyComponent( buffer);

	e->kill();
}

void np::GameObjectFactory::releasePulseEntity( ac::es::EntityPtr e)
{
	np::GraphicComponent* graphics		= e->getComponent<np::GraphicComponent>();
	np::TransformComponent* transform	= e->getComponent<np::TransformComponent>();
	np::AnimationComponent* animation	= e->getComponent<np::AnimationComponent>();
	np::PulseComponent* pulse			= e->getComponent<np::PulseComponent>();

	for (std::list<Ogre::MovableObject*>::iterator it = graphics->entities.begin(); it != graphics->entities.end(); it++)
		(*it)->setVisible( false);

	e->deactivate();

	pulsePool.push( e);
}

ac::es::EntityPtr np::GameObjectFactory::createConstructEntity( ac::es::EntityPtr hubEntity, Ogre::Degree degrees, Ogre::Real distance)
{
	np::HubComponent* _hub = hubEntity->getComponent<np::HubComponent>();
	np::TransformComponent* _transform = hubEntity->getComponent<np::TransformComponent>();
	np::GraphicComponent* _graphic = hubEntity->getComponent<np::GraphicComponent>();

	if ( _hub != NULL && _transform != NULL)
	{
		ac::es::EntityPtr e = scene->createEntity();

		//Need to fill in correct params:
		Ogre::Entity* entity = sceneManager->createEntity( "ConstructMesh");
		entity->getUserObjectBindings().setUserAny( "Entity", Ogre::Any( e));

		//Ogre::BillboardSet* constructDisplaySet = sceneManager->createBillboardSet( "constructDisplaySet");
		//constructDisplaySet->setBillboardType( Ogre::BBT_PERPENDICULAR_COMMON);

		entity->setQueryFlags( NODE_MASK);

		double tx = std::cos( degrees.valueRadians()) * distance;
		double tz = std::sin( degrees.valueRadians()) * distance;

		Ogre::MovableObject* entities[] = { entity};
		np::TransformComponent* transform = new np::TransformComponent( tx, 0.0, tz);
		transform->rotation = Ogre::Quaternion( Ogre::Radian( -degrees), Ogre::Vector3( Ogre::Vector3::UNIT_Y)) * transform->rotation;
		
		np::GraphicComponent* graphic = new np::GraphicComponent( entities, 1);

		np::ConstructComponent* construct = new np::ConstructComponent();
		construct->hub = hubEntity;
		
		e->addComponent( transform);
		e->addComponent( graphic);
		e->addComponent( construct);

		e->activate();

		_graphic->addChild( e);

		_hub->constructs.push_back( e);

		return e;
	}

	return NULL;
}

void np::GameObjectFactory::setConstruct( ac::es::EntityPtr constructEntity, np::Construct* construct)
{
	bool hasConstructComp = constructEntity->containsComponent<np::ConstructComponent>();

	if ( hasConstructComp)
	{
		np::ConstructComponent* constructComponent = constructEntity->getComponent<np::ConstructComponent>();

		constructComponent->setConstruct( construct);


	}
}

void np::GameObjectFactory::createResourceInput( ac::es::EntityPtr constructEntity, int slot)
{

}

void np::GameObjectFactory::createResourceOutput( ac::es::EntityPtr constructEntity, int slot)
{

}

void np::GameObjectFactory::createHub( ac::es::EntityPtr nodeEntity, np::NeuroPlayer* player)
{
	np::HubComponent* _hub = nodeEntity->getComponent<np::HubComponent>();
	np::GraphicComponent* graphics = nodeEntity->getComponent<np::GraphicComponent>();

	if ( _hub != NULL)
	{
		
	}
	else
	{
		_hub = new np::HubComponent( player);

		Ogre::Entity* entity = sceneManager->createEntity( "HubMesh");

		_hub->display = entity;

		entity->getUserObjectBindings().setUserAny( "Entity", Ogre::Any( nodeEntity));

		/*entity->getSubEntity(0)->getMaterial()->getTechnique(0)->getPass(0)->createTextureUnitState();
		entity->getSubEntity(0)->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setColourOperationEx(
			Ogre::LBX_SOURCE1,
			Ogre::LBS_MANUAL,
			Ogre::LBS_CURRENT,
			player->colour);*/

		entity->getSubEntity(0)->getMaterial()->setAmbient( player->colour * 0.2);
		entity->getSubEntity(0)->getMaterial()->setDiffuse( player->colour);

		graphics->addEntity( entity);
		nodeEntity->addComponent( _hub);

		for ( int i = 0; i < 6; i++)
		{
			createConstructEntity( nodeEntity, Ogre::Degree( i * 60.0), 30.0);
		}
	}
}