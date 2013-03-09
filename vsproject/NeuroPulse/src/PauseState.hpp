//|||||||||||||||||||||||||||||||||||||||||||||||

#ifndef PAUSE_STATE_HPP
#define PAUSE_STATE_HPP

//|||||||||||||||||||||||||||||||||||||||||||||||

#include "CEGUIState.h"

//|||||||||||||||||||||||||||||||||||||||||||||||

class PauseState : public CEGUIState
{
public:
    PauseState();

    DECLARE_APPSTATE_CLASS(PauseState)

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
    bool m_bQuestionActive;

	CEGUI::Window *sheet;

	bool onResume( const CEGUI::EventArgs& /*e*/);
	bool onMenu( const CEGUI::EventArgs& /*e*/);
};

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||