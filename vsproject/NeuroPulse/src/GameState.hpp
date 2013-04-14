//|||||||||||||||||||||||||||||||||||||||||||||||

#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

//|||||||||||||||||||||||||||||||||||||||||||||||

#include "CEGUIState.h"

#include "DotSceneLoader.hpp"

#include <OgreSubEntity.h>
#include <OgreMaterialManager.h>

#include <NeuroWorldSettings.h>

#include <WorldGenerator.h>
#include <NeuroWorld.h>
#include "SelectionManager.h"
#include "ConnectionPreview.h"
#include <GuiManager.h>


//|||||||||||||||||||||||||||||||||||||||||||||||

class GameState : public CEGUIState
{
public:
	GameState();

	DECLARE_APPSTATE_CLASS(GameState)

	void enter();
	void createScene();
	void exit();
	bool pause();
	void resume();

	void moveCamera();
	void getInput();
	void buildGUI();

	bool onKeyPress(const OIS::KeyEvent &keyEventRef);
	bool onKeyRelease(const OIS::KeyEvent &keyEventRef);

	bool onMouseMove(const OIS::MouseEvent &arg);
	bool onMousePress(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
	bool onMouseRelease(const OIS::MouseEvent &arg, OIS::MouseButtonID id);

	void onLeftPressed(const OIS::MouseEvent &evt);

	void update(double timeSinceLastFrame);
	ac::es::EntityPtr getEntityPtr( Ogre::Entity* entity);
	void onNodeSelected( Ogre::Entity* node);
	void onConstructSelected( Ogre::Entity* construct);
	void onConnectorSelected( Ogre::Entity* connector);
	void InjectOISKey(bool bButtonDown, OIS::KeyEvent inKey);
	bool InjectOISMouseButton(bool bButtonDown, OIS::MouseButtonID inButton);

private:
	bool						m_bQuit;

	Ogre::Vector3				m_TranslateVector;
	Ogre::Vector3				m_TranslateRelativeVector;

	float						m_MoveScale;
	Ogre::Real					m_MoveSpeed;

	float						m_MouseScrollSpeed;

	Ogre::SceneNode*			m_pCurrentObject;

	Ogre::Entity*				currentNode;
	Ogre::Entity*				currentConstruct;
	Ogre::Entity*				currentConnector;
	Ogre::Entity*				currentConstructConnection;

	Ogre::Entity*				lastSelected;

	np::SelectionManager*		selectionManager;
	np::ConnectionPreview*		connectionPreview;

	bool						m_bLMouseDown, m_bRMouseDown;

	np::NeuroWorldSettings* worldSettings;

	CEGUI::Window* sheet;

	CEGUI::Window* debug_txt;

	np::GuiManager* guiManager;

	np::NeuroWorld* neuroWorld;

	Ogre::MovableObject* selectedObject;

	bool haveSameNode( ac::es::EntityPtr node, ac::es::EntityPtr e);
};

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||