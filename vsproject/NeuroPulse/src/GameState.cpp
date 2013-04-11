//|||||||||||||||||||||||||||||||||||||||||||||||

#include "GameState.hpp"

#include <NodeComponent.h>
#include <HubComponent.h>
#include <AdvancedOgreFramework.hpp>
#include "OutputComponent.h"
#include "ConstructConnectionComponent.h"

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
	currentConstructConnection = NULL;

	lastSelected = NULL;

	selectionManager = new np::SelectionManager();
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

		Ogre::Entity* last = selectionManager->getLast();
		if ( last != NULL)
		{
			float mx = (float)evt.state.X.abs / (float)evt.state.width;
			float my = (float)evt.state.Y.abs / (float)evt.state.height;

			Ogre::Entity* selectedConstructConnection = neuroWorld->getNearestConstructConnectionFromPoint( mx, my);

			ac::es::EntityPtr lastEntity = getEntityPtr(last);

			if ( lastEntity->containsComponent<np::ConstructConnectionComponent>() && selectedConstructConnection == last)
			{
				np::ConstructConnectionComponent* constructConnection = lastEntity->getComponent<np::ConstructConnectionComponent>();

				ac::es::EntityPtr e1 = constructConnection->entity1;
				ac::es::EntityPtr e2 = constructConnection->entity2;

				selectionManager->popUntilNode();

				neuroWorld->disconnect( e1, e2);
			}
			else if ( lastEntity->containsComponent<np::ResourceInputComponent>() || lastEntity->containsComponent<np::ResourceOutputComponent>())
			{
				Ogre::Entity* selectedBud = neuroWorld->getConstructConnectorUnderPoint( mx, my);
				std::pair<int, double> nearestConnection = neuroWorld->getNearestConnectionFromPoint( mx, my, selectionManager->getLastNode());

				if ( selectedBud != NULL)
				{
					ac::es::EntityPtr connector2 = getEntityPtr( selectedBud);

					if ( connector2 != NULL)
					{
						neuroWorld->connect( lastEntity, connector2);
					}
				}
				else if ( nearestConnection.first != -1)
				{
					np::BufferComponent* buffer = lastEntity->getComponent<np::BufferComponent>();
					ac::es::EntityPtr pulseGate;

					if ( lastEntity->containsComponent<np::ResourceInputComponent>()) pulseGate = neuroWorld->gameObjectFactory->createPulseGate( nearestConnection.first, nearestConnection.second, selectionManager->getLastNode(), &buffer->getTypes(), false);
					else if ( lastEntity->containsComponent<np::ResourceOutputComponent>()) pulseGate = neuroWorld->gameObjectFactory->createPulseGate( nearestConnection.first, nearestConnection.second, selectionManager->getLastNode(), &buffer->getTypes(), true);

					neuroWorld->connect( lastEntity, pulseGate);
				}
			}
		}
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

		selectedObject = neuroWorld->getNearestConstructConnectionFromPoint( mx, my);

		if ( selectedObject != NULL)
		{
			selectionManager->popUntilNode();
			selectionManager->pushConstructConnection( selectedObject);

			return;
		}

		selectedObject = neuroWorld->getConstructConnectorUnderPoint( mx, my);

		if ( selectedObject != NULL)
		{
			if ( currentConnector != NULL) currentConnector->getParentSceneNode()->showBoundingBox(false);
			currentConnector = selectedObject;
			currentConnector->getParentSceneNode()->showBoundingBox(true);

			selectionManager->popUntilNode();
			selectionManager->pushResourceBud( selectedObject);

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

			selectionManager->popUntilNode();
			selectionManager->pushConstruct( selectedObject);

			return;
		}
		else if ( currentConstruct != NULL)
		{
			currentConstruct->getParentSceneNode()->showBoundingBox(false);
			currentConstruct = NULL;
		}
	}

	Ogre::Entity* newNode = neuroWorld->getNodeUnderPoint( mx, my);

	selectionManager->popNode();
	if ( newNode != NULL && currentNode != newNode)
	{
		onNodeSelected( newNode);

		if ( currentNode != NULL) currentNode->getParentSceneNode()->showBoundingBox(false);
		currentNode = newNode;
		currentNode->getParentSceneNode()->showBoundingBox(true);

		selectionManager->pushNode( newNode);
	}
	else if ( newNode == NULL && currentNode != NULL)
	{
		currentNode->getParentSceneNode()->showBoundingBox(false);
		currentNode = NULL;
	}
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
	if ( lastSelected != NULL)
	{
		ac::es::EntityPtr entity = getEntityPtr( lastSelected);

		if ( entity != NULL)
		{
			if ( entity->containsComponent<np::BufferComponent>() )
				debugText += CEGUI::String( "energy:      " + Ogre::StringConverter::toString( Ogre::Real( entity->getComponent<np::BufferComponent>()->getAmountOf( np::ResourceManager::getSingletonPtr()->getType("RawEnergy"))))) + "\n";
			if( entity->containsComponent<np::NodeComponent>())
			{
				debugText += CEGUI::String( "heat:        " + Ogre::StringConverter::toString( Ogre::Real( entity->getComponent<np::BufferComponent>()->getAmountOf( np::ResourceManager::getSingletonPtr()->getType("Heat"))))) + "\n";
				debugText += CEGUI::String( "temperature: " + Ogre::StringConverter::toString( Ogre::Real( entity->getComponent<np::NodeComponent>()->temperature))) + "\n";
			}
			if( entity->containsComponent<np::HubComponent>())
				debugText += CEGUI::String( "health:      " + Ogre::StringConverter::toString( Ogre::Real( entity->getComponent<np::HubComponent>()->health))) + "\n";
		}
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