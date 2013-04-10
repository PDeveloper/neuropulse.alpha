//|||||||||||||||||||||||||||||||||||||||||||||||

#include "GameState.hpp"

#include <NodeComponent.h>
#include <HubComponent.h>
#include <AdvancedOgreFramework.hpp>
#include "OutputComponent.h"

//|||||||||||||||||||||||||||||||||||||||||||||||

using namespace Ogre;

//|||||||||||||||||||||||||||||||||||||||||||||||

GameState::GameState()
{
    m_MoveSpeed			= 0.1f;
	m_MouseScrollSpeed	= 0.8f;

    m_bLMouseDown       = false;
    m_bRMouseDown       = false;
    m_bQuit             = false;
	
	// Create CEGUI interface!
	CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
	sheet = wmgr.createWindow( "DefaultWindow", "InGame/Sheet");

	debug_txt = wmgr.createWindow("TaharezLook/StaticText", "InGame/DebugTextfield");
	debug_txt->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.0, 0), CEGUI::UDim( 0.0, 0)));
	debug_txt->setSize(CEGUI::UVector2(CEGUI::UDim(0.3, 0), CEGUI::UDim(0.2, 0)));
	debug_txt->setAlpha( 0.5);

	sheet->addChildWindow( debug_txt);

	worldSettings = new np::NeuroWorldSettings();
	worldSettings->addPlayer( "PSvils", Ogre::ColourValue( 1.0, 0.0, 0.0));
	worldSettings->addPlayer( "Edib0y", Ogre::ColourValue( 0.0, 0.0, 1.0));

	currentNode = NULL;
	currentConstruct = NULL;
	currentConnector = NULL;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::enter()
{
	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Entering GameState...");

	neuroWorld = new np::NeuroWorld( worldSettings);

	m_pSceneMgr = neuroWorld->sceneManager;
	m_pCamera = neuroWorld->camera;

	/* ...oooOOOOOOOooo... */

    m_pCurrentObject = 0;

    buildGUI();

    createScene();
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool GameState::pause()
{
    OgreFramework::getSingletonPtr()->m_pLog->logMessage("Pausing GameState...");

    return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::resume()
{
	m_bQuit = false;

    OgreFramework::getSingletonPtr()->m_pLog->logMessage("Resuming GameState...");

    buildGUI();

    OgreFramework::getSingletonPtr()->m_pViewport->setCamera( m_pCamera);
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::exit()
{
    OgreFramework::getSingletonPtr()->m_pLog->logMessage("Leaving GameState...");

	delete neuroWorld;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::createScene()
{
	np::WorldGenerator generator;
	generator.generateWorld( neuroWorld);
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool GameState::onKeyPress(const OIS::KeyEvent &keyEventRef)
{
    if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_ESCAPE))
    {
        pushAppState(findByName("PauseState"));
        return true;
    }

    return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool GameState::onKeyRelease(const OIS::KeyEvent &keyEventRef)
{
    return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool GameState::onMouseMove(const OIS::MouseEvent &evt)
{
    if(m_bRMouseDown)
    {
        m_pCamera->yaw( Degree( evt.state.X.rel * -0.1f));
        m_pCamera->pitch( Degree( evt.state.Y.rel * -0.1f));
	}

	Ogre::Vector3 scrollVector( 0.0, 0.0, 0.0);

	if ( evt.state.X.abs <= 0 || evt.state.X.abs >= evt.state.width || evt.state.Y.abs <= 0 || evt.state.Y.abs >= evt.state.height)
	{
		scrollVector.x = m_MouseScrollSpeed * evt.state.X.rel;
		scrollVector.z = m_MouseScrollSpeed * evt.state.Y.rel;
	}

	m_pCamera->move( scrollVector);

    return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool GameState::onMousePress(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    if(id == OIS::MB_Left)
    {
        onLeftPressed(evt);
        m_bLMouseDown = true;
    }
    else if(id == OIS::MB_Right)
    {
        m_bRMouseDown = true;
    }

    return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool GameState::onMouseRelease(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    if(id == OIS::MB_Left)
    {
		m_bLMouseDown = false;

		if ( currentNode != NULL)
		{
			Ogre::Entity* selectedObject;
			ac::es::EntityPtr nodeEntity = getEntityPtr(currentNode);

			float mx = (float)evt.state.X.abs / (float)evt.state.width;
			float my = (float)evt.state.Y.abs / (float)evt.state.height;

			selectedObject = neuroWorld->getConstructConnectorUnderPoint( mx, my);
			std::pair<int, double> nearestConnection = neuroWorld->getNearestConnectionFromPoint( mx, my, nodeEntity);

			bool foundConnection = false;

			if ( currentConnector != NULL && selectedObject != NULL && lastSelected == currentConnector)
			{
				ac::es::EntityPtr connector1 = getEntityPtr( currentConnector);
				ac::es::EntityPtr connector2 = getEntityPtr( selectedObject);
				if ( connector2 != NULL)
				{
					np::ResourceInputComponent* input1 = connector1->getComponent<np::ResourceInputComponent>();
					np::ResourceInputComponent* input2 = connector2->getComponent<np::ResourceInputComponent>();
					np::ResourceOutputComponent* output1 = connector1->getComponent<np::ResourceOutputComponent>();
					np::ResourceOutputComponent* output2 = connector2->getComponent<np::ResourceOutputComponent>();
					np::BufferComponent* buffer1 = connector1->getComponent<np::BufferComponent>();
					np::BufferComponent* buffer2 = connector2->getComponent<np::BufferComponent>();

					if ( buffer1 != NULL && buffer2 != NULL)
					{
						Ogre::SceneNode* parent1 = currentConnector->getParentSceneNode();
						Ogre::SceneNode* parent2 = selectedObject->getParentSceneNode();

						parent1->showBoundingBox( true);

						if ( input2 != NULL && output1 != NULL && buffer2->getTypes().contains( &buffer1->getTypes()))
						{
							foundConnection = true;
							OgreFramework::getSingletonPtr()->m_pLog->logMessage( "2 thingies connected!");
							input2->connect( connector1);
							neuroWorld->gameObjectFactory->createConstructConnectionEntity( parent1->_getDerivedPosition(), parent2->_getDerivedPosition());
						}
						else if ( input1 != NULL && output2 != NULL && buffer1->getTypes().contains( &buffer2->getTypes()))
						{
							foundConnection = true;
							OgreFramework::getSingletonPtr()->m_pLog->logMessage( "2 thingies connected!");
							input1->connect( connector2);
							neuroWorld->gameObjectFactory->createConstructConnectionEntity( parent1->_getDerivedPosition(), parent2->_getDerivedPosition());
						}
						else
						{
							selectedObject->getParentSceneNode()->showBoundingBox( false);
						}
					}
				}
			}
			
			if ( nearestConnection.first > -1 && !foundConnection && currentConnector != NULL)
			{
				ac::es::EntityPtr connector1 = getEntityPtr( currentConnector);

				np::ResourceInputComponent* input1 = connector1->getComponent<np::ResourceInputComponent>();
				np::ResourceOutputComponent* output1 = connector1->getComponent<np::ResourceOutputComponent>();
				np::BufferComponent* buffer1 = connector1->getComponent<np::BufferComponent>();

				np::OutputComponent* output = nodeEntity->getComponent<np::OutputComponent>();

				OgreFramework::getSingletonPtr()->m_pLog->logMessage( "Connection FOUND!!!!!!!!!!!");

				if ( buffer1 != NULL)
				{
					ac::es::EntityPtr pulseGate;
					if ( input1 != NULL)
					{
						pulseGate = neuroWorld->gameObjectFactory->createPulseGate( nearestConnection.first, nearestConnection.second, nodeEntity, &buffer1->getTypes(), false);
						input1->connect( pulseGate);
					}
					else if ( output1 != NULL)
					{
						pulseGate = neuroWorld->gameObjectFactory->createPulseGate( nearestConnection.first, nearestConnection.second, nodeEntity, &buffer1->getTypes(), true);
						output1->connect( pulseGate);
					}
				}
			}
		}

		/*
		if( currentNode != NULL)
		{
			Ogre::Entity* entity = neuroWorld->getEntityUnderPoint( (float)evt.state.X.abs / (float)evt.state.width, (float)evt.state.Y.abs / (float)evt.state.height);

			if ( entity != NULL && !entity->getUserObjectBindings().getUserAny("Entity").isEmpty())
			{
				ac::es::EntityPtr connector = entity->getUserObjectBindings().getUserAny( "Entity").get<ac::es::EntityPtr>();
				if ( connector != NULL)
				{
					np::ResourceInputComponent* input1 = currentNode->getComponent<np::ResourceInputComponent>();
					np::ResourceInputComponent* input2 = connector->getComponent<np::ResourceInputComponent>();
					np::ResourceOutputComponent* output1 = currentNode->getComponent<np::ResourceOutputComponent>();
					np::ResourceOutputComponent* output2 = connector->getComponent<np::ResourceOutputComponent>();
					np::BufferComponent* buffer1 = currentNode->getComponent<np::BufferComponent>();
					np::BufferComponent* buffer2 = connector->getComponent<np::BufferComponent>();

					if ( buffer1 != NULL && buffer2 != NULL)
					{
						Ogre::SceneNode* parent1 = currentEntity->getParentSceneNode();
						Ogre::SceneNode* parent2 = entity->getParentSceneNode();

						parent1->showBoundingBox( true);

						if ( input2 != NULL && output1 != NULL && buffer2->getTypes().contains( &buffer1->getTypes()))
						{
							input2->connect( currentNode);
							neuroWorld->gameObjectFactory->createConstructConnectionEntity( parent1->_getDerivedPosition(), parent2->_getDerivedPosition());
						}
						else if ( input1 != NULL && output2 != NULL && buffer1->getTypes().contains( &buffer2->getTypes()))
						{
							input1->connect( connector);
							neuroWorld->gameObjectFactory->createConstructConnectionEntity( parent1->_getDerivedPosition(), parent2->_getDerivedPosition());
						}
						else
						{
							entity->getParentSceneNode()->showBoundingBox( false);
						}
					}
				}
			}
		}
		*/
    }
    else if(id == OIS::MB_Right)
    {
        m_bRMouseDown = false;
    }

    return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::onLeftPressed(const OIS::MouseEvent &evt)
{
	Ogre::Entity* entity;

	float mx = (float)evt.state.X.abs / (float)evt.state.width;
	float my = (float)evt.state.Y.abs / (float)evt.state.height;

	if ( currentNode != NULL)
	{
		Ogre::Entity* selectedObject;

		selectedObject = neuroWorld->getConstructConnectorUnderPoint( mx, my);

		if ( selectedObject != NULL)
		{
			if ( currentConnector != NULL) currentConnector->getParentSceneNode()->showBoundingBox(false);
			currentConnector = selectedObject;
			currentConnector->getParentSceneNode()->showBoundingBox(true);

			lastSelected = currentConnector;

			return;
		}
		else if ( currentConnector != NULL)
		{
			currentConnector->getParentSceneNode()->showBoundingBox(false);
			currentConnector = NULL;
		}

		selectedObject = neuroWorld->getConstructUnderPoint( mx, my);

		if ( selectedObject != NULL)
		{
			if ( currentConstruct != NULL) currentConstruct->getParentSceneNode()->showBoundingBox(false);
			currentConstruct = selectedObject;
			currentConstruct->getParentSceneNode()->showBoundingBox(true);

			lastSelected = currentConstruct;

			return;
		}
		else if ( currentConstruct != NULL)
		{
			currentConstruct->getParentSceneNode()->showBoundingBox(false);
			currentConstruct = NULL;
		}
	}

	Ogre::Entity* newNode = neuroWorld->getNodeUnderPoint( mx, my);

	if ( newNode != NULL && currentNode != newNode)
	{
		onNodeSelected( newNode);

		if ( currentNode != NULL) currentNode->getParentSceneNode()->showBoundingBox(false);
		currentNode = newNode;
		currentNode->getParentSceneNode()->showBoundingBox(true);

		lastSelected = currentNode;
	}
	else if ( newNode == NULL && currentNode != NULL)
	{
		currentNode->getParentSceneNode()->showBoundingBox(false);
		currentNode = NULL;
	}

	/*
    if( m_pCurrentObject)
    {
        m_pCurrentObject->showBoundingBox(false);
		currentNode = NULL;
		m_pCurrentObject = NULL;
    }
	//OgreFramework::getSingletonPtr()->m_pMouse->getMouseState().X.abs
	Ogre::Entity* entity = neuroWorld->getEntityUnderPoint( (float)evt.state.X.abs / (float)evt.state.width, (float)evt.state.Y.abs / (float)evt.state.height);
	if ( entity != NULL)
	{
		currentEntity = entity;
		m_pCurrentObject = entity->getParentSceneNode();
		currentNode = entity->getUserObjectBindings().getUserAny( "Entity").get<ac::es::EntityPtr>();
		m_pCurrentObject->showBoundingBox( true);
		}
		*/
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::moveCamera()
{
    if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_LSHIFT))
        m_pCamera->moveRelative(m_TranslateRelativeVector);
    m_pCamera->moveRelative(m_TranslateRelativeVector / 10);

	m_pCamera->move( m_TranslateVector);
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::getInput()
{
	if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_A))
		m_TranslateVector.x = -m_MoveScale;

	if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_D))
		m_TranslateVector.x = m_MoveScale;

	if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_W))
		m_TranslateVector.z = -m_MoveScale;

	if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_S))
		m_TranslateVector.z = m_MoveScale;

	if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_R))
		m_TranslateRelativeVector.z = -m_MoveScale;

	if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_F))
		m_TranslateRelativeVector.z = m_MoveScale;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::update(double timeSinceLastFrame)
{
    m_FrameEvent.timeSinceLastFrame = timeSinceLastFrame;

    if(m_bQuit == true)
    {
        popAppState();
        return;
    }

    m_TranslateVector = Vector3::ZERO;
	m_TranslateRelativeVector = Vector3::ZERO;

	m_MoveScale = m_MoveSpeed * timeSinceLastFrame;

	neuroWorld->update( timeSinceLastFrame);

	CEGUI::String debugText = "";
	if ( currentNode != NULL)
	{
		ac::es::EntityPtr nodeEntity = getEntityPtr( currentNode);

		if ( nodeEntity->containsComponent<np::BufferComponent>() )
			debugText += CEGUI::String( "energy:      " + Ogre::StringConverter::toString( Ogre::Real( nodeEntity->getComponent<np::BufferComponent>()->getAmountOf( np::ResourceManager::getSingletonPtr()->getType("RawEnergy"))))) + "\n";
		if( nodeEntity->getComponent<np::NodeComponent>() != NULL)
		{
			debugText += CEGUI::String( "heat:        " + Ogre::StringConverter::toString( Ogre::Real( nodeEntity->getComponent<np::BufferComponent>()->getAmountOf( np::ResourceManager::getSingletonPtr()->getType("Heat"))))) + "\n";
			debugText += CEGUI::String( "temperature: " + Ogre::StringConverter::toString( Ogre::Real( nodeEntity->getComponent<np::NodeComponent>()->temperature))) + "\n";
		}
		if( nodeEntity->getComponent<np::HubComponent>() != NULL)
			debugText += CEGUI::String( "health:      " + Ogre::StringConverter::toString( Ogre::Real( nodeEntity->getComponent<np::HubComponent>()->health))) + "\n";
	}
	debug_txt->setText( debugText);

    getInput();
    moveCamera();
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::buildGUI()
{
	CEGUI::System::getSingleton().setGUISheet( sheet);
	CEGUI::System::getSingleton().signalRedraw();
}

ac::es::EntityPtr GameState::getEntityPtr( Ogre::Entity* entity)
{
	const Ogre::Any& entityAny = entity->getUserObjectBindings().getUserAny("Entity");
	if ( !entityAny.isEmpty())
	{
		return entityAny.get<ac::es::EntityPtr>();
	}

	return NULL;
}

void GameState::onNodeSelected( Ogre::Entity* node)
{
	// at this point currentNode is still the old node.
}

void GameState::onConstructSelected( Ogre::Entity* construct)
{

}

void GameState::onConnectorSelected( Ogre::Entity* connector)
{

}