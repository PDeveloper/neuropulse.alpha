#include "ApplicationBase.h"

#include "MenuState.hpp"
#include "GameState.hpp"
#include "PauseState.hpp"
#include "IntroScreenState.h"

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

	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Initialized!");

	m_pAppStateManager = new AppStateManager();

	IntroScreenState::create( m_pAppStateManager, "IntroState");
	MenuState::create( m_pAppStateManager, "MenuState");
	GameState::create( m_pAppStateManager, "GameState");
	PauseState::create( m_pAppStateManager, "PauseState");

	m_pAppStateManager->start(m_pAppStateManager->findByName("GameState"));

	return true;
}