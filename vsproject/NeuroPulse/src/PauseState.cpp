//|||||||||||||||||||||||||||||||||||||||||||||||

#include "PauseState.hpp"

//|||||||||||||||||||||||||||||||||||||||||||||||

using namespace Ogre;

//|||||||||||||||||||||||||||||||||||||||||||||||

PauseState::PauseState()
{
    m_bQuit             = false;
    m_bQuestionActive   = false;
    m_FrameEvent        = Ogre::FrameEvent();
	
	// Create CEGUI interface!
	CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
	sheet = wmgr.createWindow("DefaultWindow", "PauseMenu/Sheet");

	CEGUI::Window *resume = wmgr.createWindow("TaharezLook/Button", "PauseMenu/ResumeButton");
	resume->setText("Resume");
	resume->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.4, 0), CEGUI::UDim( 0.45, 0)));
	resume->setSize(CEGUI::UVector2(CEGUI::UDim(0.2, 0), CEGUI::UDim(0.04, 0)));
	resume->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber( &PauseState::onResume, this));

	CEGUI::Window *menu = wmgr.createWindow("TaharezLook/Button", "PauseMenu/MenuButton");
	menu->setText("Back To Menu");
	menu->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.4, 0), CEGUI::UDim( 0.5, 0)));
	menu->setSize(CEGUI::UVector2(CEGUI::UDim(0.2, 0), CEGUI::UDim(0.04, 0)));
	menu->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber( &PauseState::onMenu, this));
	
	sheet->addChildWindow(resume);
	sheet->addChildWindow(menu);
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void PauseState::enter()
{
    OgreFramework::getSingletonPtr()->m_pLog->logMessage("Entering PauseState...");

    m_pSceneMgr = OgreFramework::getSingletonPtr()->m_pRoot->createSceneManager(ST_GENERIC, "PauseSceneMgr");
    m_pSceneMgr->setAmbientLight(Ogre::ColourValue(0.7f, 0.7f, 0.7f));

    m_pCamera = m_pSceneMgr->createCamera("PauseCam");
    m_pCamera->setPosition(Vector3(0, 25, -50));
    m_pCamera->lookAt(Vector3(0, 0, 0));
    m_pCamera->setNearClipDistance(1);

    m_pCamera->setAspectRatio(Real(OgreFramework::getSingletonPtr()->m_pViewport->getActualWidth()) /
        Real(OgreFramework::getSingletonPtr()->m_pViewport->getActualHeight()));

    OgreFramework::getSingletonPtr()->m_pViewport->setCamera(m_pCamera);

	/*
    OgreFramework::getSingletonPtr()->m_pTrayMgr->destroyAllWidgets();
    OgreFramework::getSingletonPtr()->m_pTrayMgr->showCursor();
    OgreFramework::getSingletonPtr()->m_pTrayMgr->createButton(OgreBites::TL_CENTER, "BackToGameBtn", "Return to GameState", 250);
    OgreFramework::getSingletonPtr()->m_pTrayMgr->createButton(OgreBites::TL_CENTER, "BackToMenuBtn", "Return to Menu", 250);
    OgreFramework::getSingletonPtr()->m_pTrayMgr->createButton(OgreBites::TL_CENTER, "ExitBtn", "Exit AdvancedOgreFramework", 250);
    OgreFramework::getSingletonPtr()->m_pTrayMgr->createLabel(OgreBites::TL_TOP, "PauseLbl", "Pause mode", 250);
	*/

    m_bQuit = false;

    createScene();

	CEGUI::System::getSingleton().setGUISheet(sheet);
	CEGUI::System::getSingleton().signalRedraw();
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void PauseState::createScene()
{
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void PauseState::exit()
{
    OgreFramework::getSingletonPtr()->m_pLog->logMessage("Leaving PauseState...");

    m_pSceneMgr->destroyCamera(m_pCamera);
    if(m_pSceneMgr)
        OgreFramework::getSingletonPtr()->m_pRoot->destroySceneManager(m_pSceneMgr);
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool PauseState::onKeyPress(const OIS::KeyEvent &keyEventRef)
{
    if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_ESCAPE) && !m_bQuestionActive)
    {
        m_bQuit = true;
        return true;
    }
    return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool PauseState::onKeyRelease(const OIS::KeyEvent &keyEventRef)
{
    return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool PauseState::onMouseMove(const OIS::MouseEvent &evt)
{
    return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool PauseState::onMousePress(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool PauseState::onMouseRelease(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void PauseState::update(double timeSinceLastFrame)
{
    m_FrameEvent.timeSinceLastFrame = timeSinceLastFrame;

    if(m_bQuit == true)
    {
        popAppState();
        return;
    }
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool PauseState::onResume( const CEGUI::EventArgs& /*e*/)
{
	m_bQuit = true;

	return true;
}

bool PauseState::onMenu( const CEGUI::EventArgs& /*e*/)
{
	popAllAndPushAppState(findByName("MenuState"));

	return true;
}