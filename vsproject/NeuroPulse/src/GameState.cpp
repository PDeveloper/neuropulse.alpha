//|||||||||||||||||||||||||||||||||||||||||||||||

#include "GameState.hpp"

#include <NodeComponent.h>

//|||||||||||||||||||||||||||||||||||||||||||||||

using namespace Ogre;

//|||||||||||||||||||||||||||||||||||||||||||||||

GameState::GameState()
{
    m_MoveSpeed			= 0.1f;
    m_RotateSpeed		= 0.3f;

    m_bLMouseDown       = false;
    m_bRMouseDown       = false;
    m_bQuit             = false;
    m_bSettingsMode     = false;
	
	// Create CEGUI interface!
	CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
	sheet = wmgr.createWindow( "DefaultWindow", "InGame/Sheet");

	debug_txt = wmgr.createWindow("TaharezLook/StaticText", "InGame/DebugTextfield");
	debug_txt->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.0, 0), CEGUI::UDim( 0.0, 0)));
	debug_txt->setSize(CEGUI::UVector2(CEGUI::UDim(0.3, 0), CEGUI::UDim(0.2, 0)));
	debug_txt->setAlpha( 0.5);

	sheet->addChildWindow( debug_txt);

	pulseSettings = new np::PulseSystemSettings( 800.0);
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::enter()
{
	m_pSceneMgr = OgreFramework::getSingletonPtr()->m_pRoot->createSceneManager( Ogre::ST_GENERIC, "GlobalSceneMgr");

	neuroWorld = new np::NeuroWorld();

	esScene = new ac::es::Scene();
	gameObjectFactory = new np::GameObjectFactory( m_pSceneMgr, esScene);

	eventManager = new np::EventManager();

	/* init systems and shit */
	reactionSystem = new np::ReactionSystem();
	outputSystem = new np::OutputSystem( eventManager, pulseSettings);
	animationSystem = new np::AnimationSystem();
	graphicSystem = new np::GraphicSystem(m_pSceneMgr);
	connectionDisplaySystem = new np::ConnectionDisplaySystem( m_pSceneMgr);
	pulseSystem = new np::PulseSystem( gameObjectFactory, eventManager);

	esScene->insertEntitySystem( reactionSystem);
	esScene->insertEntitySystem( outputSystem);

	esScene->insertEntitySystem( animationSystem);

	esScene->insertEntitySystem( graphicSystem);
	esScene->insertEntitySystem( connectionDisplaySystem);
	
	esScene->insertEntitySystem( pulseSystem);
	/* ................. */

    OgreFramework::getSingletonPtr()->m_pLog->logMessage("Entering GameState...");
	
    m_pSceneMgr->setAmbientLight(Ogre::ColourValue(0.4f, 0.4f, 0.4f));
	m_pSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

    m_pRSQ = m_pSceneMgr->createRayQuery(Ray());
    m_pRSQ->setQueryMask(OGRE_HEAD_MASK);

    m_pCamera = m_pSceneMgr->createCamera("GameCamera");
    m_pCamera->setPosition(Vector3(5, 420, 60));
    m_pCamera->lookAt(Vector3(5, 20, -60));
    m_pCamera->setNearClipDistance(5);

    m_pCamera->setAspectRatio(Real(OgreFramework::getSingletonPtr()->m_pViewport->getActualWidth()) /
        Real(OgreFramework::getSingletonPtr()->m_pViewport->getActualHeight()));

    OgreFramework::getSingletonPtr()->m_pViewport->setCamera(m_pCamera);
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
    OgreFramework::getSingletonPtr()->m_pLog->logMessage("Resuming GameState...");

    buildGUI();

    OgreFramework::getSingletonPtr()->m_pViewport->setCamera(m_pCamera);
    m_bQuit = false;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::exit()
{
    OgreFramework::getSingletonPtr()->m_pLog->logMessage("Leaving GameState...");

    m_pSceneMgr->destroyCamera(m_pCamera);
    m_pSceneMgr->destroyQuery(m_pRSQ);
    if(m_pSceneMgr)
        OgreFramework::getSingletonPtr()->m_pRoot->destroySceneManager(m_pSceneMgr);
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::createScene()
{
	Ogre::Light* directionalLight = m_pSceneMgr->createLight("SunLight");
	directionalLight->setType( Ogre::Light::LT_DIRECTIONAL);
    directionalLight->setDiffuseColour( Ogre::ColourValue( 0.25, 0.25, 0.25));
    directionalLight->setSpecularColour( Ogre::ColourValue( 0.25, 0.25, 0.25));

	directionalLight->setDirection( Ogre::Vector3( 0.5, -1, -1 ));

	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane( "GroundMesh", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
													plane, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
	
	Ogre::Entity* entGround = m_pSceneMgr->createEntity("GroundEntity", "GroundMesh");
	m_pSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entGround);

	entGround->setMaterialName("GroundMaterial");
	entGround->setCastShadows(false);

	np::WorldGenerator generator;
	generator.generateWorld( neuroWorld, gameObjectFactory, 9);
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool GameState::onKeyPress(const OIS::KeyEvent &keyEventRef)
{
    if(m_bSettingsMode == true)
    {
        if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_S))
        {
            //OgreBites::SelectMenu* pMenu = (OgreBites::SelectMenu*)OgreFramework::getSingletonPtr()->m_pTrayMgr->getWidget("ChatModeSelMenu");
            //if(pMenu->getSelectionIndex() + 1 < (int)pMenu->getNumItems())
            //    pMenu->selectItem(pMenu->getSelectionIndex() + 1);
        }

        if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_W))
        {
            //OgreBites::SelectMenu* pMenu = (OgreBites::SelectMenu*)OgreFramework::getSingletonPtr()->m_pTrayMgr->getWidget("ChatModeSelMenu");
            //if(pMenu->getSelectionIndex() - 1 >= 0)
            //    pMenu->selectItem(pMenu->getSelectionIndex() - 1);
        }
    }

    if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_ESCAPE))
    {
        pushAppState(findByName("PauseState"));
        return true;
    }

    if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_I))
    {
        /*
		if(m_pDetailsPanel->getTrayLocation() == OgreBites::TL_NONE)
        {
            OgreFramework::getSingletonPtr()->m_pTrayMgr->moveWidgetToTray(m_pDetailsPanel, OgreBites::TL_TOPLEFT, 0);
            m_pDetailsPanel->show();
        }
        else
        {
            OgreFramework::getSingletonPtr()->m_pTrayMgr->removeWidgetFromTray(m_pDetailsPanel);
            m_pDetailsPanel->hide();
        }
		*/
    }

    if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_TAB))
    {
        m_bSettingsMode = !m_bSettingsMode;
        return true;
    }

    if(m_bSettingsMode && OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_RETURN) ||
        OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_NUMPADENTER))
    {
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
        m_pCamera->yaw(Degree(evt.state.X.rel * -0.1f));
        m_pCamera->pitch(Degree(evt.state.Y.rel * -0.1f));
	}

	if ( evt.state.X.abs < 0)
	{
		m_TranslateVector.x = m_MoveScale * evt.state.X.abs;
	}
	else if ( evt.state.X.abs > evt.state.width)
	{
		m_TranslateVector.x = m_MoveScale * ( evt.state.X.abs - evt.state.width);
	}

	if ( evt.state.Y.abs < 0)
	{
		m_TranslateVector.y = m_MoveScale * evt.state.Y.abs;
	}
	else if ( evt.state.Y.abs > evt.state.height)
	{
		m_TranslateVector.y = m_MoveScale * ( evt.state.Y.abs - evt.state.height);
	}

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
    /*if(m_pCurrentObject)
    {
        m_pCurrentObject->showBoundingBox(false);
        m_pCurrentEntity->getSubEntity(1)->setMaterial(m_pOgreHeadMat);
    }

    Ogre::Ray mouseRay = m_pCamera->getCameraToViewportRay(OgreFramework::getSingletonPtr()->m_pMouse->getMouseState().X.abs / float(evt.state.width),
        OgreFramework::getSingletonPtr()->m_pMouse->getMouseState().Y.abs / float(evt.state.height));
    m_pRSQ->setRay(mouseRay);
    m_pRSQ->setSortByDistance(true);

    Ogre::RaySceneQueryResult &result = m_pRSQ->execute();
    Ogre::RaySceneQueryResult::iterator itr;

    for(itr = result.begin(); itr != result.end(); itr++)
    {
        if(itr->movable)
        {
            OgreFramework::getSingletonPtr()->m_pLog->logMessage("MovableName: " + itr->movable->getName());
            m_pCurrentObject = m_pSceneMgr->getEntity(itr->movable->getName())->getParentSceneNode();
            OgreFramework::getSingletonPtr()->m_pLog->logMessage("ObjName " + m_pCurrentObject->getName());
            m_pCurrentObject->showBoundingBox(true);
            m_pCurrentEntity = m_pSceneMgr->getEntity(itr->movable->getName());
            m_pCurrentEntity->getSubEntity(1)->setMaterial(m_pOgreHeadMatHigh);
            break;
        }
    }*/
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
    if(m_bSettingsMode == false)
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

    m_MoveScale = m_MoveSpeed   * timeSinceLastFrame;
    m_RotScale  = m_RotateSpeed * timeSinceLastFrame;

    m_TranslateVector = Vector3::ZERO;
	m_TranslateRelativeVector = Vector3::ZERO;

	reactionSystem->setDeltaTime( timeSinceLastFrame);
	outputSystem->globalTick( timeSinceLastFrame);

	ac::es::EntityPtr e = neuroWorld->nodes.at( 0);
	np::NodeComponent* node = e->getComponent<np::NodeComponent>();

	CEGUI::String debugText = "";
	debugText += CEGUI::String( "timeSinceLastFrame:" + Ogre::StringConverter::toString( Ogre::Real( timeSinceLastFrame))) + "\n";
	debugText += CEGUI::String( "globalPulseTime:" + Ogre::StringConverter::toString( Ogre::Real( pulseSettings->globalPulseTime))) + "\n";
	debugText += CEGUI::String( "node0 energy:" + Ogre::StringConverter::toString( Ogre::Real( node->currentEnergy))) + "\n";
	debugText += CEGUI::String( Ogre::StringConverter::toString( Ogre::Real( outputSystem->timeSinceLastPulse))) + "\n";
	debug_txt->setText( debugText);

	esScene->update();

	eventManager->refresh();

    getInput();
    moveCamera();
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::buildGUI()
{
	CEGUI::System::getSingleton().setGUISheet( sheet);
	CEGUI::System::getSingleton().signalRedraw();

    //OgreFramework::getSingletonPtr()->m_pTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    //OgreFramework::getSingletonPtr()->m_pTrayMgr->showLogo(OgreBites::TL_BOTTOMRIGHT);
    //OgreFramework::getSingletonPtr()->m_pTrayMgr->showCursor();

    //Ogre::StringVector items;
    //items.push_back("debug val");
    //items.push_back("Mode");

    //m_pDetailsPanel = OgreFramework::getSingletonPtr()->m_pTrayMgr->createParamsPanel(OgreBites::TL_TOPLEFT, "DetailsPanel", 180, items);
    //m_pDetailsPanel->show();

    //Ogre::StringVector chatModes;
    //chatModes.push_back("Solid mode");
    //chatModes.push_back("Wireframe mode");
    //chatModes.push_back("Point mode");
    //OgreFramework::getSingletonPtr()->m_pTrayMgr->createLongSelectMenu(OgreBites::TL_TOPRIGHT, "ChatModeSelMenu", "ChatMode", 200, 3, chatModes);
}