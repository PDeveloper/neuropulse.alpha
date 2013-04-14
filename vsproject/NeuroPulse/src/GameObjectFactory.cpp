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
#include <ConstructConnectionComponent.h>
#include <HubComponent.h>
#include <BufferComponent.h>

#include <TweenState.h>

#include <AdvancedOgreFramework.hpp>
#include <NeuroWorld.h>

#include <OgreProcedural\Procedural.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include "HubConstructionComponent.h"
#include "CameraComponent.h"

#include <OgreOggSound.h>

np::GameObjectFactory::GameObjectFactory( np::NeuroWorld* world) :
	pulsePool()
{
	this->world = world;
	this->sceneManager = world->sceneManager;
	this->scene = world->esScene;

	Ogre::MovableObject::setDefaultQueryFlags(0);

	generateMeshes();
}

np::GameObjectFactory::~GameObjectFactory(void)
{

}

void np::GameObjectFactory::generateMeshes(void)
{
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
	Ogre::MeshPtr resMesh = Procedural::SphereGenerator().setRadius( 2.0).setNumSegments( 6).setNumRings(6).realizeMesh("ResourceBudMesh");
	resMesh->getSubMesh(0)->setMaterialName( "ResourceBudMaterial");

	///////// GROUND MESH
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshPtr groundMesh = Ogre::MeshManager::getSingleton().createPlane( "GroundMesh", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);

	groundMesh->getSubMesh(0)->setMaterialName( "TerrainMaterial");

	///////// HUB MESH

	Procedural::Shape hubShape = Procedural::RectangleShape().setHeight( 0.5).setWidth( 5.0).realizeShape();
	hubShape.translate( 10.0, 12.0);

	Ogre::MeshPtr hubMesh = Procedural::Lathe().setShapeToExtrude( &hubShape).setNumSeg( 24).realizeMesh( "HubMesh");
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

	///////// CONSTRUCT CONNECTION MESH
	Procedural::Path connectorPath = Procedural::LinePath().betweenPoints(	Ogre::Vector3( 0.0, 0.0, 0.0),
		Ogre::Vector3( 0.0, 0.0, 100.0)).realizePath();

	Procedural::Shape connectorCircle = Procedural::CircleShape().setRadius( 0.8).setNumSeg( 10).realizeShape();
	Procedural::Track connectorTrack = Procedural::Track(Procedural::Track::AM_RELATIVE_LINEIC).addKeyFrame( 0.0, 1.0).addKeyFrame( 0.5, 0.75).addKeyFrame( 1.0, 1.0);
	Ogre::MeshPtr constructConnectionMesh = Procedural::Extruder().setExtrusionPath( &connectorPath).setScaleTrack( &connectorTrack).setShapeToExtrude( &connectorCircle).realizeMesh( "ConstructConnectionMesh");
	constructConnectionMesh->getSubMesh(0)->setMaterialName( "ConstructConnectionMaterial");
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

	OgreOggSound::OgreOggSoundManager::getSingletonPtr()->createSound( "PulseEmitted" + Ogre::StringConverter::toString( e->getId()), "NeuroPulse_PulseEmitted_mono.wav");
	
	//Need to fill in correct params:
	Ogre::Entity* entity = sceneManager->createEntity( "NodeMesh");
	entity->getUserObjectBindings().setUserAny( "Entity", Ogre::Any( e));
	entity->setQueryFlags( NODE_MASK);
	
	Ogre::Entity* entities[] = { entity};

	np::GraphicComponent* graphic = new np::GraphicComponent( entities, 1);
	np::TransformComponent* transform = new np::TransformComponent( x, 0.0, y);
	np::ReactionComponent* reactor = new np::ReactionComponent( reactorOutput);
	np::NodeComponent* node = new np::NodeComponent( threshold);
	np::OutputComponent* output = new np::OutputComponent();
	np::BufferComponent* buffer = new np::BufferComponent( np::ResourceRequirement::ANY);

	np::HubConstructionComponent* hubConstruction = new np::HubConstructionComponent();

	e->addComponent( graphic);
	e->addComponent( transform);
	e->addComponent( reactor);
	e->addComponent( node);
	e->addComponent( output);
	e->addComponent( buffer);
	e->addComponent( hubConstruction);

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
	np::HubConstructionComponent* hubConstruction = e->getComponent<np::HubConstructionComponent>();

	e->destroyComponent( graphics);
	e->destroyComponent( transform);
	e->destroyComponent( node);
	e->destroyComponent( reactor);
	e->destroyComponent( output);
	e->destroyComponent( buffer);
	e->destroyComponent( hubConstruction);
	if ( hub != NULL) e->destroyComponent( hub);

	e->kill();
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

		OgreFramework::getSingletonPtr()->m_pLog->logMessage( "New Pulse Entity created");

		Ogre::Entity* entity = sceneManager->createEntity( "PulseMesh");
		entity->setCastShadows( false);
		
		Ogre::Entity* entities[] = { entity};
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

		graphic->show();
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
	np::GraphicComponent* graphic		= e->getComponent<np::GraphicComponent>();
	np::TransformComponent* transform	= e->getComponent<np::TransformComponent>();
	np::AnimationComponent* animation	= e->getComponent<np::AnimationComponent>();
	np::PulseComponent* pulse			= e->getComponent<np::PulseComponent>();

	graphic->hide();

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

		entity->setQueryFlags( CONSTRUCT_MASK);

		double tx = std::cos( degrees.valueRadians()) * distance;
		double tz = std::sin( degrees.valueRadians()) * distance;

		Ogre::Entity* entities[] = { entity};
		np::TransformComponent* transform = new np::TransformComponent( tx, 0.0, tz);
		transform->rotation = Ogre::Quaternion( Ogre::Radian( -degrees), Ogre::Vector3( Ogre::Vector3::UNIT_Y)) * transform->rotation;
		
		np::GraphicComponent* graphic = new np::GraphicComponent( entities, 1);

		np::ConstructComponent* construct = new np::ConstructComponent();
		construct->hub = hubEntity;
		construct->parent = hubEntity;
		
		e->addComponent( transform);
		e->addComponent( graphic);
		e->addComponent( construct);

		e->activate();

		_graphic->addChild( e);

		_hub->addConstruct( e);

		return e;
	}

	return NULL;
}

void np::GameObjectFactory::killConstructEntity( ac::es::EntityPtr e)
{
	np::GraphicComponent* graphic		= e->getComponent<np::GraphicComponent>();
	np::TransformComponent* transform	= e->getComponent<np::TransformComponent>();
	np::ConstructComponent* construct    = e->getComponent<np::ConstructComponent>();

	graphic->parent->removeChild( e);

	e->destroyComponent( graphic);
	e->destroyComponent( transform);
	e->destroyComponent( construct);

	e->kill();
}

void np::GameObjectFactory::setConstruct( ac::es::EntityPtr constructEntity, np::Construct* construct)
{
	bool hasConstructComp = constructEntity->containsComponent<np::ConstructComponent>();

	if ( hasConstructComp)
	{
		np::ConstructComponent* constructComponent = constructEntity->getComponent<np::ConstructComponent>();
		np::GraphicComponent* graphicComponent = constructEntity->getComponent<np::GraphicComponent>();

		constructComponent->setConstruct( construct);

		int i;
		for ( i = 0; i < construct->inputRequirements.size(); i++)
			construct->inputs.push_back( createResourceBud( constructEntity, &construct->inputRequirements[i], true, i));

		for ( i = 0; i < construct->outputRequirements.size(); i++)
			construct->outputs.push_back( createResourceBud( constructEntity, &construct->outputRequirements[i], false, i));

		Ogre::MaterialPtr material = graphicComponent->entities.front()->getSubEntity(0)->getMaterial()->clone( construct->getName() + "Material");
		material->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setColourOperationEx(
			Ogre::LBX_SOURCE1,
			Ogre::LBS_MANUAL,
			Ogre::LBS_CURRENT,
			construct->colour);

		material->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(
			Ogre::LBX_SOURCE1,
			Ogre::LBS_MANUAL,
			Ogre::LBS_CURRENT,
			0.4);

		graphicComponent->entities.front()->getSubEntity(0)->setMaterial( material);
	}
}

void np::GameObjectFactory::removeConstruct( ac::es::EntityPtr constructEntity, np::Construct* construct)
{
	bool hasConstructComp = constructEntity->containsComponent<np::ConstructComponent>();

	if ( hasConstructComp)
	{
		np::ConstructComponent* constructComponent = constructEntity->getComponent<np::ConstructComponent>();
		np::GraphicComponent* graphicComponent = constructEntity->getComponent<np::GraphicComponent>();

		np::ResourceInputComponent* input;
		np::ResourceOutputComponent* output;

		int i;
		for ( i = 0; i < construct->inputs.size(); i++)
		{
			input = construct->inputs[i]->getComponent<np::ResourceInputComponent>();
			if ( input->target != NULL)
			{
				if ( input->target->containsComponent<np::PulseGateComponent>())
				{
					killPulseGate( input->target);
				}
				else
				{
					input->target->getComponent<np::ResourceOutputComponent>()->disconnect();
				}

				killConstructConnectionEntity( input->connection);
			}

			killResourceBud( construct->inputs[i]);
		}

		for ( i = 0; i < construct->outputs.size(); i++)
		{
			output = construct->outputs[i]->getComponent<np::ResourceOutputComponent>();
			if ( output->target != NULL)
			{
				if ( output->target->containsComponent<np::PulseGateComponent>())
				{
					killPulseGate( output->target);
				}
				else
				{
					output->target->getComponent<np::ResourceInputComponent>()->disconnect();
				}

				killConstructConnectionEntity( output->connection);
			}

			killResourceBud( construct->outputs[i]);
		}

		constructComponent->setConstruct( NULL);

		graphicComponent->entities.front()->getSubEntity(0)->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setColourOperationEx(
			Ogre::LBX_SOURCE1,
			Ogre::LBS_MANUAL,
			Ogre::LBS_CURRENT,
			Ogre::ColourValue( 0.0, 0.0, 0.0));

		graphicComponent->entities.front()->getSubEntity(0)->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setAlphaOperation(
			Ogre::LBX_SOURCE1,
			Ogre::LBS_MANUAL,
			Ogre::LBS_CURRENT,
			0.2);
	}
}

ac::es::EntityPtr np::GameObjectFactory::createResourceBud( ac::es::EntityPtr constructEntity, np::ResourceRequirement* requirement, bool isInput, int slot)
{
	np::GraphicComponent* parent = constructEntity->getComponent<np::GraphicComponent>();
	np::ConstructComponent* construct = constructEntity->getComponent<np::ConstructComponent>();
	
	ac::es::EntityPtr e = scene->createEntity();

	int mult = (int)isInput * -2 + 1;

	Ogre::Entity* entity = sceneManager->createEntity( "ResourceBudMesh");
	entity->setCastShadows( false);
	entity->getUserObjectBindings().setUserAny( "Entity", Ogre::Any( e));
	entity->setQueryFlags( CONSTRUCT_CONNECTOR_MASK);

	std::vector<np::ResourceType*> types = np::ResourceManager::getSingletonPtr()->getTypes( requirement);

	Ogre::ColourValue budColour = types[0]->colour;
	for ( int i = 1; i < types.size(); i++)
	{
		budColour += types[i]->colour;
	}

	budColour /= types.size();

	Ogre::MaterialPtr material = entity->getSubEntity(0)->getMaterial()->clone( entity->getName());
	material->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setColourOperationEx(
		Ogre::LBX_SOURCE1,
		Ogre::LBS_MANUAL,
		Ogre::LBS_CURRENT,
		budColour);
	entity->setMaterial( material);

	Ogre::Entity* entities[] = { entity};
	np::GraphicComponent* graphic = new np::GraphicComponent( entities, 1);
	np::TransformComponent* transform = new np::TransformComponent( -8.0 * mult, 13.0, ( -4.0 + slot * 4.0) * mult);
	np::BufferComponent* buffer = new np::BufferComponent( *requirement, 10.0);

	e->addComponent( graphic);
	e->addComponent( transform);
	e->addComponent( buffer);

	if ( isInput)
	{
		np::ResourceInputComponent* input = new np::ResourceInputComponent();
		input->parent = constructEntity;
		input->hub = construct->hub;

		input->disconnect();
		if ( input->target != NULL)
		{
			input->target->getComponent<np::ResourceOutputComponent>()->disconnect();
			killConstructConnectionEntity( input->connection);
		}

		e->addComponent( input);
	}
	else
	{
		np::ResourceOutputComponent* output = new np::ResourceOutputComponent();
		output->parent = constructEntity;
		output->hub = construct->hub;

		output->disconnect();
		if ( output->target != NULL)
		{
			output->target->getComponent<np::ResourceInputComponent>()->disconnect();
			killConstructConnectionEntity( output->connection);
		}

		e->addComponent( output);
	}

	parent->addChild( e);

	construct->hub->getComponent<np::HubComponent>()->addBud( e);

	e->activate();

	return e;
}

void np::GameObjectFactory::killResourceBud( ac::es::EntityPtr e )
{
	np::GraphicComponent* graphic = e->getComponent<np::GraphicComponent>();
	np::TransformComponent* transform = e->getComponent<np::TransformComponent>();
	np::BufferComponent* buffer = e->getComponent<np::BufferComponent>();

	graphic->parent->removeChild( e);

	e->destroyComponent( graphic);
	e->destroyComponent( transform);
	e->destroyComponent( buffer);

	if ( e->containsComponent<np::ResourceInputComponent>())
	{
		np::ResourceInputComponent* input = e->getComponent<np::ResourceInputComponent>();

		input->hub->getComponent<np::HubComponent>()->removeBud( e);
		e->destroyComponent( input);
	}
	else if ( e->containsComponent<np::ResourceOutputComponent>())
	{
		np::ResourceOutputComponent* output = e->getComponent<np::ResourceOutputComponent>();

		output->hub->getComponent<np::HubComponent>()->removeBud( e);
		e->destroyComponent( output);
	}

	e->kill();
}

ac::es::EntityPtr np::GameObjectFactory::createPulseGate( int connection, double position, ac::es::EntityPtr nodeEntity, np::ResourceRequirement* requirement, bool isInput)
{
	np::OutputComponent* _output = nodeEntity->getComponent<np::OutputComponent>();
	np::TransformComponent* _transform1 = nodeEntity->getComponent<np::TransformComponent>();
	np::TransformComponent* _transform2 = _output->connections[connection]->target->parent->getComponent<np::TransformComponent>();

	ac::es::EntityPtr e = scene->createEntity();

	Ogre::Entity* entity = sceneManager->createEntity( "ResourceBudMesh");
	entity->setCastShadows( false);
	entity->getUserObjectBindings().setUserAny( "Entity", Ogre::Any( e));
	entity->setQueryFlags( CONSTRUCT_CONNECTOR_MASK);

	std::vector<np::ResourceType*> types = np::ResourceManager::getSingletonPtr()->getTypes( requirement);

	Ogre::ColourValue budColour = types[0]->colour;
	for ( int i = 1; i < types.size(); i++)
	{
		budColour += types[i]->colour;
	}

	budColour /= types.size();

	Ogre::MaterialPtr material = entity->getSubEntity(0)->getMaterial()->clone( entity->getName());
	material->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setColourOperationEx(
		Ogre::LBX_SOURCE1,
		Ogre::LBS_MANUAL,
		Ogre::LBS_CURRENT,
		budColour);
	entity->setMaterial( material);

	Ogre::Entity* entities[] = { entity};
	np::GraphicComponent* graphic = new np::GraphicComponent( entities, 1);
	np::TransformComponent* transform = new np::TransformComponent();
	transform->position = _transform1->position + position * ( _transform2->position - _transform1->position);
	transform->position.y = 2.0;
	OgreFramework::getSingletonPtr()->m_pLog->logMessage( Ogre::StringConverter::toString( _transform1->position));
	OgreFramework::getSingletonPtr()->m_pLog->logMessage( Ogre::StringConverter::toString( transform->position));

	np::BufferComponent* buffer = new np::BufferComponent( *requirement, 10.0);

	np::PulseGateComponent* pulseGate = new np::PulseGateComponent( connection, position, nodeEntity);

	e->addComponent( graphic);
	e->addComponent( transform);
	e->addComponent( buffer);
	e->addComponent( pulseGate);

	if ( isInput)
	{
		np::ResourceInputComponent* input = new np::ResourceInputComponent();
		input->parent = nodeEntity;
		input->hub = nodeEntity;
		e->addComponent( input);
	}
	else
	{
		np::ResourceOutputComponent* output = new np::ResourceOutputComponent();
		output->parent = nodeEntity;
		output->hub = nodeEntity;
		e->addComponent( output);
	}

	e->activate();

	np::HubComponent* hubComponent = nodeEntity->getComponent<np::HubComponent>();
	hubComponent->addGate( e);

	return e;
}

void np::GameObjectFactory::killPulseGate( ac::es::EntityPtr e )
{
	np::GraphicComponent* graphic		= e->getComponent<np::GraphicComponent>();
	np::TransformComponent* transform	= e->getComponent<np::TransformComponent>();
	np::BufferComponent* buffer			= e->getComponent<np::BufferComponent>();
	np::PulseGateComponent* pulseGate	= e->getComponent<np::PulseGateComponent>();

	np::ResourceInputComponent* input	= e->getComponent<np::ResourceInputComponent>();
	np::ResourceOutputComponent* output = e->getComponent<np::ResourceOutputComponent>();

	np::OutputComponent* outputComponent = pulseGate->nodeEntity->getComponent<np::OutputComponent>();
	outputComponent->connections[ pulseGate->connectionIndex]->removeFeed( e);

	e->destroyComponent( graphic);
	e->destroyComponent( transform);
	e->destroyComponent( buffer);
	e->destroyComponent( pulseGate);

	if ( input != NULL)
	{
		input->hub->getComponent<np::HubComponent>()->removeGate( e);
		e->destroyComponent( input);
	}

	if ( output != NULL)
	{
		output->hub->getComponent<np::HubComponent>()->removeGate( e);
		e->destroyComponent( output);
	}

	e->kill();
}

ac::es::EntityPtr np::GameObjectFactory::createProxyHubEntity( ac::es::EntityPtr nodeEntity, np::NeuroPlayer* player)
{
	ac::es::EntityPtr e = scene->createEntity();

	np::GraphicComponent* parentGraphic = nodeEntity->getComponent<np::GraphicComponent>();

	Ogre::Entity* entity = sceneManager->createEntity( "HubMesh");

	entity->getUserObjectBindings().setUserAny( "Entity", Ogre::Any( e));

	Ogre::MaterialPtr material = entity->getSubEntity(0)->getMaterial()->clone( entity->getName());
	material->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setColourOperationEx(
		Ogre::LBX_SOURCE1,
		Ogre::LBS_MANUAL,
		Ogre::LBS_CURRENT,
		player->colour);
	entity->setMaterial( material);

	Ogre::Entity* entities[] = { entity};
	np::GraphicComponent* graphic = new np::GraphicComponent( entities, 1);
	np::TransformComponent* transform = new np::TransformComponent();

	e->addComponent( graphic);
	e->addComponent( transform);

	e->activate();

	parentGraphic->addChild( e);

	return e;
}

void np::GameObjectFactory::killProxyHubEntity( ac::es::EntityPtr e)
{
	np::GraphicComponent* graphic = e->getComponent<np::GraphicComponent>();
	np::TransformComponent* transform = e->getComponent<np::TransformComponent>();

	graphic->parent->removeChild( e);

	e->destroyComponent( graphic);
	e->destroyComponent( transform);

	e->kill();
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

		Ogre::MaterialPtr material = entity->getSubEntity(0)->getMaterial()->clone( entity->getName());
		material->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setColourOperationEx(
			Ogre::LBX_SOURCE1,
			Ogre::LBS_MANUAL,
			Ogre::LBS_CURRENT,
			player->colour);
		entity->setMaterial( material);

		graphics->addEntity( entity);
		nodeEntity->addComponent( _hub);

		for ( int i = 0; i < 6; i++)
		{
			createConstructEntity( nodeEntity, Ogre::Degree( i * 60.0), 30.0);
		}

		_hub->hideStructures();
	}
}

void np::GameObjectFactory::killHub( ac::es::EntityPtr nodeEntity)
{
	np::HubComponent* hub = nodeEntity->getComponent<np::HubComponent>();

	std::list<ac::es::EntityPtr>::iterator iterator;

	std::list<ac::es::EntityPtr> buds = hub->buds;
	iterator = buds.begin();
	while ( iterator != buds.end())
	{
		killResourceBud( *(iterator++));
	}

	std::list<ac::es::EntityPtr> gates = hub->gates;
	iterator = gates.begin();
	while ( iterator != gates.end())
	{
		killPulseGate( *(iterator++));
	}

	std::list<ac::es::EntityPtr> constructs = hub->constructs;
	iterator = constructs.begin();
	while ( iterator != constructs.end())
	{
		killConstructEntity( *(iterator++));
	}

	std::list<ac::es::EntityPtr> connections = hub->connections;
	iterator = connections.begin();
	while ( iterator != connections.end())
	{
		killConstructConnectionEntity( *(iterator++));
	}

	np::GraphicComponent* graphic = nodeEntity->getComponent<np::GraphicComponent>();
	graphic->removeEntity( hub->display);

	nodeEntity->destroyComponent(hub);
}

ac::es::EntityPtr np::GameObjectFactory::createConstructConnectionEntity(  ac::es::EntityPtr e1, ac::es::EntityPtr e2)
{
	np::GraphicComponent* _graphic1 = e1->getComponent<np::GraphicComponent>();
	np::GraphicComponent* _graphic2 = e2->getComponent<np::GraphicComponent>();

	const Ogre::Vector3* position1;
	const Ogre::Vector3* position2;
	if ( _graphic1->node != NULL)	position1 = &_graphic1->node->_getDerivedPosition();
	else							position1 = &e1->getComponent<np::TransformComponent>()->position;

	if ( _graphic2->node != NULL)	position2 = &_graphic2->node->_getDerivedPosition();
	else							position2 = &e2->getComponent<np::TransformComponent>()->position;

	double distance = position1->distance( *position2);
	ac::es::EntityPtr e = scene->createEntity();

	Ogre::Entity* entity = sceneManager->createEntity( "ConstructConnectionMesh");
	entity->setCastShadows( false);
	entity->getUserObjectBindings().setUserAny( "Entity", Ogre::Any( e));
	entity->setQueryFlags( CONSTRUCT_CONNECTION_MASK);

	Ogre::Entity* entities[] = { entity};
	np::GraphicComponent* graphic = new np::GraphicComponent( entities, 1);
	np::TransformComponent* transform = new np::TransformComponent();
	np::ConstructConnectionComponent* connection = new np::ConstructConnectionComponent( e1, e2);
	
	double d = distance / 100.0;

	transform->position = *position1;
	transform->rotation = Ogre::Vector3::UNIT_Z.getRotationTo( *position2 - *position1);
	transform->scale = Ogre::Vector3( 1.0, 1.0, d);

	e->addComponent( graphic);
	e->addComponent( transform);
	e->addComponent( connection);

	np::ResourceInputComponent* input;
	np::HubComponent* hub;
	if ( e1->containsComponent<np::ResourceInputComponent>())
	{
		input = e1->getComponent<np::ResourceInputComponent>();
		hub = input->hub->getComponent<np::HubComponent>();
		hub->addConnection( e);
		connection->hub = input->hub;
	}
	else if ( e2->containsComponent<np::ResourceInputComponent>())
	{
		input = e2->getComponent<np::ResourceInputComponent>();
		hub = input->hub->getComponent<np::HubComponent>();
		hub->addConnection( e);
		connection->hub = input->hub;
	}

	e->activate();

	return e;
}

ac::es::EntityPtr np::GameObjectFactory::createRawConstructConnectionEntity( const Ogre::Vector3& position1, const Ogre::Vector3& position2)
{
	double distance = position1.distance( position2);
	ac::es::EntityPtr e = scene->createEntity();

	Ogre::Entity* entity = sceneManager->createEntity( "ConstructConnectionMesh");
	entity->setCastShadows( false);
	entity->getUserObjectBindings().setUserAny( "Entity", Ogre::Any( e));

	Ogre::Entity* entities[] = { entity};
	np::GraphicComponent* graphic = new np::GraphicComponent( entities, 1);
	np::TransformComponent* transform = new np::TransformComponent();

	double d = distance / 100.0;

	transform->position = position1;
	transform->rotation = Ogre::Vector3::UNIT_Z.getRotationTo( position2 - position1);
	transform->scale = Ogre::Vector3( 1.0, 1.0, d);

	e->addComponent( graphic);
	e->addComponent( transform);

	e->activate();

	return e;
}

void np::GameObjectFactory::killConstructConnectionEntity( ac::es::EntityPtr e)
{
	np::GraphicComponent* graphic = e->getComponent<np::GraphicComponent>();
	np::TransformComponent* transform = e->getComponent<np::TransformComponent>();
	np::ConstructConnectionComponent* connection = e->getComponent<np::ConstructConnectionComponent>();

	connection->hub->getComponent<np::HubComponent>()->removeConnection( e);

	e->destroyComponent( graphic);
	e->destroyComponent( transform);
	e->destroyComponent( connection);

	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Construct Connection KILLED!");

	e->kill();
}

ac::es::EntityPtr np::GameObjectFactory::createCamera( Ogre::Camera* camera )
{
	ac::es::EntityPtr e = scene->createEntity();

	np::TransformComponent* transform = new np::TransformComponent();
	np::CameraComponent* cameraComponent = new np::CameraComponent( camera);

	e->addComponent( transform);
	e->addComponent( cameraComponent);

	e->activate();

	return e;
}
