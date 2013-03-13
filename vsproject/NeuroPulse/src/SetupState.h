//|||||||||||||||||||||||||||||||||||||||||||||||

#ifndef SETUP_STATE_HPP
#define SETUP_STATE_HPP

//|||||||||||||||||||||||||||||||||||||||||||||||

#include "CEGUIState.h"

//|||||||||||||||||||||||||||||||||||||||||||||||

class SetupState : public CEGUIState
{
public:
	SetupState();

	DECLARE_APPSTATE_CLASS(SetupState)

	void enter();
	void createScene();
	void exit();

	bool onKeyPress(const OIS::KeyEvent &keyEventRef);
	bool onKeyRelease(const OIS::KeyEvent &keyEventRef);

	bool onMouseMove(const OIS::MouseEvent &evt);
	bool onMousePress(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
	bool onMouseRelease(const OIS::MouseEvent &evt, OIS::MouseButtonID id);

	void update(double timeSinceLastFrame);

private:
	bool m_bQuit;

	CEGUI::Window *sheet;
};

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||