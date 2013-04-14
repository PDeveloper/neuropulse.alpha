#pragma once
#include "CEGUIState.h"

class IntroScreenState : public CEGUIState
{
public:
	IntroScreenState(void);

	DECLARE_APPSTATE_CLASS(IntroScreenState)

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

	float mangoLogoAlpha;

	CEGUI::Window *sheet;
	CEGUI::Window* mangoMachineLogo;
};

