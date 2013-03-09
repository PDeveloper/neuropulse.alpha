//|||||||||||||||||||||||||||||||||||||||||||||||

#include "MenuState.hpp"

//|||||||||||||||||||||||||||||||||||||||||||||||

using namespace Ogre;

//|||||||||||||||||||||||||||||||||||||||||||||||

MenuState::MenuState()
{
    m_bQuit         = false;
    m_FrameEvent    = Ogre::FrameEvent();
	
	// Create CEGUI interface!
	CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
	sheet = wmgr.createWindow("DefaultWindow", "MainMenu/Sheet");

	CEGUI::Window *play = wmgr.createWindow("TaharezLook/Button", "MainMenu/PlayButton");
	play->setText("Play");
	play->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.4, 0), CEGUI::UDim( 0.45, 0)));
	play->setSize(CEGUI::UVector2(CEGUI::UDim(0.2, 0), CEGUI::UDim(0.04, 0)));
	play->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber( &MenuState::onPlay, this));

	CEGUI::Window *options = wmgr.createWindow("TaharezLook/Button", "MainMenu/OptionsButton");
	options->setText("Options");
	options->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.4, 0), CEGUI::UDim( 0.5, 0)));
	options->setSize(CEGUI::UVector2(CEGUI::UDim(0.2, 0), CEGUI::UDim(0.04, 0)));
	options->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber( &MenuState::onOptions, this));

	CEGUI::Window *quit = wmgr.createWindow("TaharezLook/Button", "MainMenu/QuitButton");
	quit->setText("Quit");
	quit->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.4, 0), CEGUI::UDim( 0.55, 0)));
	quit->setSize(CEGUI::UVector2(CEGUI::UDim(0.2, 0), CEGUI::UDim(0.04, 0)));
	quit->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber( &MenuState::onQuit, this));
	
	sheet->addChildWindow(play);
	sheet->addChildWindow(options);
	sheet->addChildWindow(quit);
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void MenuState::enter()
{
	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Entering MenuState...");

    m_pSceneMgr = OgreFramework::getSingletonPtr()->m_pRoot->createSceneManager(ST_GENERIC, "MenuSceneMgr");
    m_pSceneMgr->setAmbientLight(Ogre::ColourValue(0.7f, 0.7f, 0.7f));

    m_pCamera = m_pSceneMgr->createCamera("MenuCam");
    m_pCamera->setPosition(Vector3(0, 25, -50));
    m_pCamera->lookAt(Vector3(0, 0, 0));
    m_pCamera->setNearClipDistance(1);

    m_pCamera->setAspectRatio(Real(OgreFramework::getSingletonPtr()->m_pViewport->getActualWidth()) /
        Real(OgreFramework::getSingletonPtr()->m_pViewport->getActualHeight()));

    OgreFramework::getSingletonPtr()->m_pViewport->setCamera(m_pCamera);

    createScene();

	CEGUI::System::getSingleton().setGUISheet(sheet);
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void MenuState::createScene()
{
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void MenuState::exit()
{
    OgreFramework::getSingletonPtr()->m_pLog->logMessage("Leaving MenuState...");

    m_pSceneMgr->destroyCamera(m_pCamera);
    if(m_pSceneMgr)
        OgreFramework::getSingletonPtr()->m_pRoot->destroySceneManager(m_pSceneMgr);
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool MenuState::onKeyPress(const OIS::KeyEvent &keyEventRef)
{
    if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_ESCAPE))
    {
        m_bQuit = true;

        return true;
    }

    return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool MenuState::onKeyRelease(const OIS::KeyEvent &keyEventRef)
{
    return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool MenuState::onMouseMove(const OIS::MouseEvent &evt)
{
    return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool MenuState::onMousePress(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool MenuState::onMouseRelease(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void MenuState::update(double timeSinceLastFrame)
{
    m_FrameEvent.timeSinceLastFrame = timeSinceLastFrame;

    if(m_bQuit == true)
    {
        shutdown();
        return;
    }
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool MenuState::onPlay( const CEGUI::EventArgs& /*e*/)
{
	changeAppState( findByName( "GameState"));

	return true;
}

bool MenuState::onOptions( const CEGUI::EventArgs& /*e*/)
{
	return true;
}

bool MenuState::onQuit( const CEGUI::EventArgs& /*e*/)
{
	m_bQuit = true;

	return true;
}