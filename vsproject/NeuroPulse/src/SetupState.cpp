#include "SetupState.h"

//|||||||||||||||||||||||||||||||||||||||||||||||

using namespace Ogre;

//|||||||||||||||||||||||||||||||||||||||||||||||

SetupState::SetupState()
{
	m_bQuit         = false;
	m_FrameEvent    = Ogre::FrameEvent();

	// Create CEGUI interface!
	CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
	sheet = wmgr.createWindow("DefaultWindow", "MainMenu/Sheet");
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void SetupState::enter()
{
	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Entering SetupState...");

	m_pSceneMgr = OgreFramework::getSingletonPtr()->m_pRoot->createSceneManager(ST_GENERIC, "SetupSceneMgr");
	m_pSceneMgr->setAmbientLight(Ogre::ColourValue(0.7f, 0.7f, 0.7f));

	m_pCamera = m_pSceneMgr->createCamera("SetupCam");
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

void SetupState::createScene()
{
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void SetupState::exit()
{
	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Leaving SetupState...");

	m_pSceneMgr->destroyCamera(m_pCamera);
	if(m_pSceneMgr)
		OgreFramework::getSingletonPtr()->m_pRoot->destroySceneManager(m_pSceneMgr);
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool SetupState::onKeyPress(const OIS::KeyEvent &keyEventRef)
{
	if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_ESCAPE))
	{
		m_bQuit = true;

		return true;
	}

	return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool SetupState::onKeyRelease(const OIS::KeyEvent &keyEventRef)
{
	return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool SetupState::onMouseMove(const OIS::MouseEvent &evt)
{
	return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool SetupState::onMousePress(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
	return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool SetupState::onMouseRelease(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
	return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void SetupState::update(double timeSinceLastFrame)
{
	m_FrameEvent.timeSinceLastFrame = timeSinceLastFrame;

	if(m_bQuit == true)
	{
		shutdown();
		return;
	}
}