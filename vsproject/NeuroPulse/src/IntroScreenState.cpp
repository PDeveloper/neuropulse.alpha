#include "IntroScreenState.h"


IntroScreenState::IntroScreenState(void)
{
	m_bQuit         = false;
	m_FrameEvent    = Ogre::FrameEvent();

	mangoLogoAlpha = 0.0;

	// Create CEGUI interface!
	CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
	sheet = wmgr.createWindow("DefaultWindow", "IntroScreen/Sheet");

	CEGUI::ImagesetManager::getSingleton().createFromImageFile("MangoMachineLogo", "mangoMachineLogo_1.png");
	mangoMachineLogo = wmgr.createWindow("TaharezLook/StaticImage", "IntroScreen/MangoLogo");
	mangoMachineLogo->setProperty( "Image", "set:MangoMachineLogo image:full_image");
	mangoMachineLogo->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.5, -180.0), CEGUI::UDim( 0.5, -350.0)));
	mangoMachineLogo->setSize(CEGUI::UVector2(CEGUI::UDim(0.0, 380.0), CEGUI::UDim(0.0, 400.0)));
	mangoMachineLogo->setProperty( "FrameEnabled", "False");

	CEGUI::ImagesetManager::getSingleton().createFromImageFile("Quotes", "quotes.png");
	quotes = wmgr.createWindow("TaharezLook/StaticImage", "IntroScreen/Quotes");
	quotes->setProperty( "Image", "set:Quotes image:full_image");
	quotes->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.5, -256.0), CEGUI::UDim( 0.5, 50.0)));
	quotes->setSize(CEGUI::UVector2(CEGUI::UDim(0.0, 512.0), CEGUI::UDim(0.0, 256.0)));
	quotes->setProperty( "FrameEnabled", "False");

	quotes->setAlpha( 0.0);
	mangoMachineLogo->setAlpha( 0.0);

	sheet->addChildWindow( mangoMachineLogo);
	sheet->addChildWindow( quotes);
}

void IntroScreenState::enter()
{
	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Entering MenuState...");

	m_pSceneMgr = OgreFramework::getSingletonPtr()->m_pRoot->createSceneManager(Ogre::ST_GENERIC, "IntroSceneMgr");
	m_pSceneMgr->setAmbientLight( Ogre::ColourValue(0.7f, 0.7f, 0.7f));

	m_pCamera = m_pSceneMgr->createCamera("IntroCam");
	m_pCamera->setPosition( Ogre::Vector3(0, 25, -50));
	m_pCamera->lookAt( Ogre::Vector3(0, 0, 0));
	m_pCamera->setNearClipDistance(1);

	m_pCamera->setAspectRatio( Ogre::Real(OgreFramework::getSingletonPtr()->m_pViewport->getActualWidth()) /
		 Ogre::Real(OgreFramework::getSingletonPtr()->m_pViewport->getActualHeight()));

	OgreFramework::getSingletonPtr()->m_pViewport->setCamera(m_pCamera);

	createScene();

	CEGUI::System::getSingleton().setGUISheet(sheet);
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void IntroScreenState::createScene()
{
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void IntroScreenState::exit()
{
	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Leaving MenuState...");

	m_pSceneMgr->destroyCamera(m_pCamera);
	if(m_pSceneMgr)
		OgreFramework::getSingletonPtr()->m_pRoot->destroySceneManager(m_pSceneMgr);
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool IntroScreenState::onKeyPress(const OIS::KeyEvent &keyEventRef)
{
	if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_ESCAPE))
	{
		changeAppState( findByName( "MenuState"));

		return true;
	}

	return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool IntroScreenState::onKeyRelease(const OIS::KeyEvent &keyEventRef)
{
	return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool IntroScreenState::onMouseMove(const OIS::MouseEvent &evt)
{
	return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool IntroScreenState::onMousePress(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
	return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool IntroScreenState::onMouseRelease(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
	return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void IntroScreenState::update(double timeSinceLastFrame)
{
	m_FrameEvent.timeSinceLastFrame = timeSinceLastFrame;

	mangoLogoAlpha += timeSinceLastFrame;

	if ( mangoLogoAlpha < 3000.0)
	{
		mangoMachineLogo->setAlpha( mangoLogoAlpha / 3000.0);
	}
	else if ( mangoLogoAlpha > 10000.0)
	{

	}
	else if ( mangoLogoAlpha > 7000.0)
	{
		mangoMachineLogo->setAlpha( 1.0 - ( mangoLogoAlpha - 7000.0) / 3000.0);
	}
	else
	{
		mangoMachineLogo->setAlpha( 1.0);
	}

	if ( mangoLogoAlpha > 500.0 && mangoLogoAlpha < 3500.0)
	{
		quotes->setAlpha( ( mangoLogoAlpha - 500.0) / 3000.0);
	}
	else if ( mangoLogoAlpha > 11000.0)
	{
		changeAppState( findByName( "MenuState"));
	}
	else if ( mangoLogoAlpha > 8000.0)
	{
		quotes->setAlpha( 1.0 - ( mangoLogoAlpha - 8000.0) / 3000.0);
	}
	else if ( mangoLogoAlpha > 500.0)
	{
		quotes->setAlpha( 1.0);
	}
}
