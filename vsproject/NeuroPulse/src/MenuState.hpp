//|||||||||||||||||||||||||||||||||||||||||||||||

#ifndef MENU_STATE_HPP
#define MENU_STATE_HPP

//|||||||||||||||||||||||||||||||||||||||||||||||

#include "CEGUIState.h"

//|||||||||||||||||||||||||||||||||||||||||||||||

class MenuState : public CEGUIState
{
public:
    MenuState();

	DECLARE_APPSTATE_CLASS(MenuState)

	void enter();
	void createScene();
	void exit();

	bool onKeyPress(const OIS::KeyEvent &keyEventRef);
	bool onKeyRelease(const OIS::KeyEvent &keyEventRef);

	bool onMouseMove(const OIS::MouseEvent &evt);
	bool onMousePress(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
	bool onMouseRelease(const OIS::MouseEvent &evt, OIS::MouseButtonID id);

	void update(double timeSinceLastFrame);

	bool onPlay( const CEGUI::EventArgs& /*e*/);
	bool onOptions( const CEGUI::EventArgs& /*e*/);
	bool onQuit( const CEGUI::EventArgs& /*e*/);

private:
	bool m_bQuit;

	CEGUI::Window *sheet;
};

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||