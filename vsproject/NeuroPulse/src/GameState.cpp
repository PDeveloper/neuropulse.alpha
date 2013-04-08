//|||||||||||||||||||||||||||||||||||||||||||||||

#include "GameState.hpp"

#include <NodeComponent.h>
#include <AdvancedOgreFramework.hpp>

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

		if( currentNode != NULL)
		{
			Ogre::Entity* entity = neuroWorld->getEntityUnderPoint( (float)evt.state.X.abs / (float)evt.state.width, (float)evt.state.Y.abs / (float)evt.state.height);
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
    else if(id == OIS::MB_Right)
    {
        m_bRMouseDown = false;
    }

    return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::onLeftPressed(const OIS::MouseEvent &evt)
{
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
	if ( currentNode != NULL && currentNode->containsComponent<np::BufferComponent>())
	{
		debugText += CEGUI::String( "energy:" + Ogre::StringConverter::toString( Ogre::Real( currentNode->getComponent<np::BufferComponent>()->getAmountOf( np::ResourceManager::getSingletonPtr()->getType("RawEnergy"))))) + "\n";
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