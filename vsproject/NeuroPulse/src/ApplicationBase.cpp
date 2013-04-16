#include "ApplicationBase.h"

#include "MenuState.hpp"
#include "GameState.hpp"
#include "PauseState.hpp"
#include "IntroScreenState.h"
#include "OgreOggSoundManager.h"
#include "OgreSceneManager.h"

ApplicationBase::ApplicationBase(void)
{
	m_pAppStateManager = 0;
}

ApplicationBase::~ApplicationBase(void)
{
	delete m_pAppStateManager;
	delete OgreFramework::getSingletonPtr();
}

bool ApplicationBase::run(void)
{
	new OgreFramework();
	if( !OgreFramework::getSingletonPtr()->initOgre("NeuroPulse: Alpha", 0, 0))
		return false;

	Ogre::SceneManager* m_pSceneMgr = OgreFramework::getSingletonPtr()->m_pRoot->createSceneManager( Ogre::ST_GENERIC, "SoundSceneMgr");
	OgreOggSound::OgreOggSoundManager::getSingletonPtr()->init();

	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Initialized!");

	m_pAppStateManager = new AppStateManager();

	IntroScreenState::create( m_pAppStateManager, "IntroState");
	MenuState::create( m_pAppStateManager, "MenuState");
	GameState::create( m_pAppStateManager, "GameState");
	PauseState::create( m_pAppStateManager, "PauseState");

	m_pAppStateManager->start(m_pAppStateManager->findByName("IntroState"));

	return true;
}