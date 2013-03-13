//|||||||||||||||||||||||||||||||||||||||||||||||

#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

//|||||||||||||||||||||||||||||||||||||||||||||||

#include "CEGUIState.h"

#include "DotSceneLoader.hpp"

#include <OgreSubEntity.h>
#include <OgreMaterialManager.h>

#include <GameObjectFactory.h>

#include <GraphicSystem.h>
#include <AnimationSystem.h>
#include <OutputSystem.h>
#include <ReactionSystem.h>
#include <ConnectionDisplaySystem.h>
#include <PulseSystem.h>

#include <PulseSystemSettings.h>

#include <EventManager.h>

#include <WorldGenerator.h>
#include <NeuroWorld.h>

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

private:
	Ogre::SceneNode*			m_pOgreHeadNode;
	Ogre::Entity*				m_pOgreHeadEntity;
	Ogre::MaterialPtr			m_pOgreHeadMat;
	Ogre::MaterialPtr			m_pOgreHeadMatHigh;

	bool						m_bQuit;

	Ogre::Vector3				m_TranslateVector;
	Ogre::Vector3				m_TranslateRelativeVector;
	Ogre::Real					m_MoveSpeed;
	Ogre::Degree				m_RotateSpeed;
	float						m_MoveScale;
	float						m_MouseScrollSpeed;
	Ogre::Degree				m_RotScale;

	Ogre::RaySceneQuery*		m_pRSQ;
	Ogre::SceneNode*			m_pCurrentObject;
	Ogre::Entity*				m_pCurrentEntity;
	bool						m_bLMouseDown, m_bRMouseDown;

	ac::es::Scene* esScene;

	np::GameObjectFactory* gameObjectFactory;

	// Systems
	np::GraphicSystem* graphicSystem;
	np::AnimationSystem* animationSystem;
	np::OutputSystem* outputSystem;
	np::ReactionSystem* reactionSystem;
	np::ConnectionDisplaySystem* connectionDisplaySystem;
	np::PulseSystem* pulseSystem;

	np::EventManager* eventManager;

	np::PulseSystemSettings* pulseSettings;

	CEGUI::Window *sheet;
	CEGUI::Window* debug_txt;

	np::NeuroWorld* neuroWorld;

	ac::es::EntityPtr selectedEntity;
};

//|||||||||||||||||||||||||||||||||||||||||||||||

#endif

//|||||||||||||||||||||||||||||||||||||||||||||||