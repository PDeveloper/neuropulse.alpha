#pragma once

//|||||||||||||||||||||||||||||||||||||||||||||||

#include "AppState.hpp"

//|||||||||||||||||||||||||||||||||||||||||||||||

class CEGUIState : public AppState
{
public:
	virtual bool onKeyPress( const OIS::KeyEvent &keyEventRef) = 0;
	virtual bool onKeyRelease( const OIS::KeyEvent &keyEventRef) = 0;

	virtual bool onMouseMove( const OIS::MouseEvent &evt) = 0;
	virtual bool onMousePress( const OIS::MouseEvent &evt, OIS::MouseButtonID id) = 0;
	virtual bool onMouseRelease( const OIS::MouseEvent &evt, OIS::MouseButtonID id) = 0;

protected:
	CEGUIState(void){};

private:
	bool keyPressed( const OIS::KeyEvent &keyEventRef)
	{
		OgreFramework::getSingletonPtr()->keyPressed(keyEventRef);
		
		onKeyPress( keyEventRef);

		return true;
	}

	bool keyReleased( const OIS::KeyEvent &keyEventRef)
	{
		OgreFramework::getSingletonPtr()->keyReleased(keyEventRef);

		onKeyRelease( keyEventRef);

		return true;
	}

	bool mouseMoved( const OIS::MouseEvent &evt)
	{
		OgreFramework::getSingletonPtr()->mouseMoved( evt);

		onMouseMove( evt);

		return true;
	}

	bool mousePressed( const OIS::MouseEvent &evt, OIS::MouseButtonID id)
	{
		OgreFramework::getSingletonPtr()->mousePressed( evt, id);

		onMousePress( evt, id);

		return true;
	}

	bool mouseReleased( const OIS::MouseEvent &evt, OIS::MouseButtonID id)
	{
		OgreFramework::getSingletonPtr()->mouseReleased( evt, id);

		onMouseRelease( evt, id);

		return true;
	}
};

