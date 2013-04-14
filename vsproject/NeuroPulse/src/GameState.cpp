//|||||||||||||||||||||||||||||||||||||||||||||||

#include "GameState.hpp"

#include <OgreOggSound.h>

#include <NodeComponent.h>
#include <HubComponent.h>
#include <ConstructComponent.h>
#include <AdvancedOgreFramework.hpp>
#include <ResourceInputComponent.h>
#include <ResourceOutputComponent.h>
#include "OutputComponent.h"
#include "ConstructConnectionComponent.h"
#include "GraphicComponent.h"
#include <RefineryConstructionConstruct.h>
#include <SexyEnergyBufferConstruction.h>

//|||||||||||||||||||||||||||||||||||||||||||||||

using namespace Ogre;

//|||||||||||||||||||||||||||||||||||||||||||||||

GameState::GameState()
{
	m_MoveSpeed			= 0.1f;
	m_MouseScrollSpeed	= 0.8f;

	m_bLMouseDown       = false;
	m_bRMouseDown       = false;
	m_bQuit             = false;
	
	// Create CEGUI interface!
	CEGUI::WindowManager* wmgr = &CEGUI::WindowManager::getSingleton();
	sheet = wmgr->createWindow( "DefaultWindow", "RootSheet");
	//sheet->setSize( CEGUI::UVector2( CEGUI::UDim( 0, 800), CEGUI::UDim( 0, 600)));
	sheet->setPosition(CEGUI::UVector2( CEGUI::UDim( 0, 0), CEGUI::UDim( 0, 0)));
	sheet->setMousePassThroughEnabled(true);
	
	

	//Debug shit
	debug_txt = wmgr->createWindow("TaharezLook/StaticText", "InGame/DebugTextfield");
	debug_txt->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.0, 0), CEGUI::UDim( 0.0, 0)));
	debug_txt->setSize(CEGUI::UVector2(CEGUI::UDim(0.3, 0), CEGUI::UDim(0.2, 0)));
	debug_txt->setAlpha( 0.5);
	debug_txt->setMousePassThroughEnabled(true);

	//sheet->addChildWindow( debug_txt);

	//Gui manager
	

	guiManager = new np::GuiManager(wmgr);

	sheet->addChildWindow(guiManager->sheet);
	guiManager->sheet->setSize( CEGUI::UVector2( CEGUI::UDim( 0, 800), CEGUI::UDim( 0, 600)));
	guiManager->sheet->setPosition(CEGUI::UVector2( CEGUI::UDim( 0, 0), CEGUI::UDim( 0, 0)));

	worldSettings = new np::NeuroWorldSettings();
	worldSettings->addPlayer( "PSvils", Ogre::ColourValue( 1.0, 0.0, 0.0));
	worldSettings->addPlayer( "Edib0y", Ogre::ColourValue( 0.0, 0.0, 1.0));

	currentNode = NULL;
	currentConstruct = NULL;
	currentConnector = NULL;
	currentConstructConnection = NULL;

	lastSelected = NULL;

	selectionManager = new np::SelectionManager();
	connectionPreview = NULL;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::enter()
{
	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Entering GameState...");

	neuroWorld = new np::NeuroWorld( worldSettings);

	connectionPreview = new np::ConnectionPreview( neuroWorld->gameObjectFactory->createRawConstructConnectionEntity( Ogre::Vector3(), Ogre::Vector3::UNIT_Z));
	connectionPreview->hide();

	guiManager->constructInfoPanel->buildMenu->update();

	m_pSceneMgr = neuroWorld->sceneManager;
	m_pCamera = neuroWorld->camera;

	/* ...oooOOOOOOOooo... */

	m_pCurrentObject = 0;

	OgreOggSound::OgreOggSoundManager::getSingletonPtr()->init();
	OgreOggSound::OgreOggISound* mainLoop = OgreOggSound::OgreOggSoundManager::getSingletonPtr()->createSound( "GameLoop", "Neuronic.ogg", true, true);
	mainLoop->disable3D( true);
	mainLoop->setVolume( 0.6);
	mainLoop->play();

	OgreOggSound::OgreOggSoundManager::getSingletonPtr()->createSound( "SelectObject", "NeuroPulse_SelectObject.ogg")->disable3D( true);
	OgreOggSound::OgreOggSoundManager::getSingletonPtr()->createSound( "GoodBud", "NeuroPulse_GoodBud.ogg")->disable3D( true);
	OgreOggSound::OgreOggSoundManager::getSingletonPtr()->createSound( "BadBud", "NeuroPulse_BadBud.ogg")->disable3D( true);

	OgreOggSound::OgreOggSoundManager* soundManager = OgreOggSound::OgreOggSoundManager::getSingletonPtr();
	OgreOggSound::OgreOggISound* sound;
	sound = OgreOggSound::OgreOggSoundManager::getSingletonPtr()->createSound( "ConstructBuilt", "NeuroPulse_ConstructBuilt_mono.wav");
	sound->setReferenceDistance( 140.0);
	sound = OgreOggSound::OgreOggSoundManager::getSingletonPtr()->createSound( "HubBuilt", "NeuroPulse_HubBuilt_mono.wav");
	sound->setReferenceDistance( 200.0);

	nodeSelector = neuroWorld->gameObjectFactory->createNodeSelector();

	buildGUI();

	createScene();
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool GameState::pause()
{
	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Pausing GameState...");

	return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::resume()
{
	m_bQuit = false;

	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Resuming GameState...");

	buildGUI();

	OgreFramework::getSingletonPtr()->m_pViewport->setCamera( m_pCamera);
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::exit()
{
	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Leaving GameState...");

	OgreOggSound::OgreOggSoundManager::getSingletonPtr()->destroyAllSounds();

	if ( connectionPreview != NULL) delete connectionPreview;
	delete neuroWorld;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::createScene()
{
	np::WorldGenerator generator;
	generator.generateWorld( neuroWorld);
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool GameState::onKeyPress(const OIS::KeyEvent &keyEventRef)
{
	if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_ESCAPE))
	{
		pushAppState(findByName("PauseState"));
		return true;
	}

	InjectOISKey(true, keyEventRef);

	return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool GameState::onKeyRelease(const OIS::KeyEvent &keyEventRef)
{

	InjectOISKey(false, keyEventRef);

	return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool GameState::onMouseMove(const OIS::MouseEvent &evt)
{
	if ( m_bLMouseDown)
	{
		connectionPreview;

		Ogre::Entity* last = selectionManager->getLast();
		if ( last != NULL)
		{
			float mx = (float)evt.state.X.abs / (float)evt.state.width;
			float my = (float)evt.state.Y.abs / (float)evt.state.height;

			ac::es::EntityPtr lastEntity = getEntityPtr(last);

			if ( lastEntity->containsComponent<np::ResourceInputComponent>() || lastEntity->containsComponent<np::ResourceOutputComponent>())
			{
				Ogre::Entity* selectedBud = neuroWorld->getConstructConnectorUnderPoint( mx, my);
				std::pair<int, double> nearestConnection = neuroWorld->getNearestConnectionFromPoint( mx, my, selectionManager->getLastNode());

				if ( lastEntity->containsComponent<np::PulseGateComponent>() && nearestConnection.first != -1)
				{
					nearestConnection = neuroWorld->getNearestConnectionFromPoint( mx, my, selectionManager->getLastNode(), 10.0);

					ac::es::EntityPtr lastNode = selectionManager->getLastNode();
					np::TransformComponent* transform = lastNode->getComponent<np::TransformComponent>();
					np::OutputComponent* output = lastNode->getComponent<np::OutputComponent>();

					np::PulseGateComponent* pulseGate = lastEntity->getComponent<np::PulseGateComponent>();
					np::TransformComponent* gateTransform = lastEntity->getComponent<np::TransformComponent>();

					ac::es::EntityPtr targetNode = output->connections[ nearestConnection.first]->target->parent;
					np::TransformComponent* transform2 = targetNode->getComponent<np::TransformComponent>();

					pulseGate->position = nearestConnection.second;
					gateTransform->position = transform->position + nearestConnection.second * ( transform2->position - transform->position);

					if ( nearestConnection.first != pulseGate->connectionIndex)
					{
						ac::es::EntityPtr hub = pulseGate->nodeEntity;
						np::OutputComponent* output = hub->getComponent<np::OutputComponent>();

						output->connections[ pulseGate->connectionIndex]->removeFeed( lastEntity);
						output->connections[ nearestConnection.first]->addFeed( lastEntity);

						pulseGate->connectionIndex = nearestConnection.first;
					}
				}
				else if ( selectedBud != NULL)
				{
					ac::es::EntityPtr connector2 = getEntityPtr( selectedBud);

					if ( connector2 != NULL && !connector2->containsComponent<np::PulseGateComponent>())
					{
						np::GraphicComponent* graphic = connector2->getComponent<np::GraphicComponent>();
						connectionPreview->updateTarget( graphic->node->_getDerivedPosition());

						if ( neuroWorld->isValid( connector2, lastEntity)) connectionPreview->setColor( Ogre::ColourValue( 0.0, 1.0, 0.0));
						else connectionPreview->setColor( Ogre::ColourValue( 1.0, 0.0, 0.0));
					}
				}
				else if ( nearestConnection.first != -1)
				{
					ac::es::EntityPtr lastNode = selectionManager->getLastNode();
					np::TransformComponent* transform = lastNode->getComponent<np::TransformComponent>();
					np::OutputComponent* output = lastNode->getComponent<np::OutputComponent>();

					ac::es::EntityPtr targetNode = output->connections[ nearestConnection.first]->target->parent;
					np::TransformComponent* transform2 = targetNode->getComponent<np::TransformComponent>();

					connectionPreview->updateTarget( transform->position + nearestConnection.second * ( transform2->position - transform->position));
					
					connectionPreview->setColor( Ogre::ColourValue( 0.0, 1.0, 0.0));
				}
				else
				{
					connectionPreview->updateTarget( neuroWorld->getRayPlane( mx, my));

					connectionPreview->setColor( Ogre::ColourValue( 1.0, 0.0, 0.0));
				}
			}
		}
	}
    else if(m_bRMouseDown)
    {
		neuroWorld->getCameraTransform()->rotation = Ogre::Quaternion( Degree( evt.state.X.rel * -0.1f), Vector3::UNIT_Y)
			* neuroWorld->getCameraTransform()->rotation
			* Ogre::Quaternion( Degree( evt.state.Y.rel * -0.1f), Vector3::UNIT_X);
	}

	Ogre::Vector3 scrollVector( 0.0, 0.0, 0.0);

	if ( evt.state.X.abs <= 0 || evt.state.X.abs >= evt.state.width || evt.state.Y.abs <= 0 || evt.state.Y.abs >= evt.state.height)
	{
		scrollVector.x = m_MouseScrollSpeed * evt.state.X.rel;
		scrollVector.z = m_MouseScrollSpeed * evt.state.Y.rel;
	}

	neuroWorld->getCameraTransform()->position += scrollVector;

	CEGUI::System::getSingleton().injectMousePosition(evt.state.X.rel, evt.state.Y.rel);

	return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool GameState::onMousePress(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
	if(!InjectOISMouseButton(true, id))
	{
		if(id == OIS::MB_Left)
		{
			onLeftPressed(evt);
			m_bLMouseDown = true;
		}
		else if(id == OIS::MB_Right)
		{
			m_bRMouseDown = true;
		}
	}

	

	return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

bool GameState::onMouseRelease(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
	if(id == OIS::MB_Left)
	{
		m_bLMouseDown = false;
		connectionPreview->hide();

		Ogre::Entity* last = selectionManager->getLast();
		if ( last != NULL && selectionManager->getLastNode() != NULL)
		{
			float mx = (float)evt.state.X.abs / (float)evt.state.width;
			float my = (float)evt.state.Y.abs / (float)evt.state.height;

			Ogre::Entity* selectedConstructConnection = neuroWorld->getNearestConstructConnectionFromPoint( mx, my);

			ac::es::EntityPtr lastEntity = getEntityPtr(last);

			if ( lastEntity->containsComponent<np::ConstructConnectionComponent>() && selectedConstructConnection == last)
			{
				np::ConstructConnectionComponent* constructConnection = lastEntity->getComponent<np::ConstructConnectionComponent>();

				ac::es::EntityPtr e1 = constructConnection->entity1;
				ac::es::EntityPtr e2 = constructConnection->entity2;

				selectionManager->popUntilNode();

				neuroWorld->disconnect( e1, e2);
				playSound( "GoodBud");
			}
			else if ( ( lastEntity->containsComponent<np::ResourceInputComponent>() || lastEntity->containsComponent<np::ResourceOutputComponent>()) && !lastEntity->containsComponent<np::PulseGateComponent>())
			{
				Ogre::Entity* selectedBud = neuroWorld->getConstructConnectorUnderPoint( mx, my);
				std::pair<int, double> nearestConnection = neuroWorld->getNearestConnectionFromPoint( mx, my, selectionManager->getLastNode());

				if ( selectedBud != NULL)
				{
					ac::es::EntityPtr connector2 = getEntityPtr( selectedBud);

					if ( connector2 != NULL && !connector2->containsComponent<np::PulseGateComponent>())
					{
						if ( neuroWorld->connect( lastEntity, connector2)) playSound( "GoodBud");
						else playSound( "BadBud");
					}
				}
				else if ( nearestConnection.first != -1)
				{
					np::BufferComponent* buffer = lastEntity->getComponent<np::BufferComponent>();
					ac::es::EntityPtr pulseGate;

					if ( lastEntity->containsComponent<np::ResourceInputComponent>()) pulseGate = neuroWorld->gameObjectFactory->createPulseGate( nearestConnection.first, nearestConnection.second, selectionManager->getLastNode(), &buffer->getTypes(), false);
					else if ( lastEntity->containsComponent<np::ResourceOutputComponent>()) pulseGate = neuroWorld->gameObjectFactory->createPulseGate( nearestConnection.first, nearestConnection.second, selectionManager->getLastNode(), &buffer->getTypes(), true);

					np::OutputComponent* output = selectionManager->getLastNode()->getComponent<np::OutputComponent>();
					output->connections[ nearestConnection.first]->addFeed( pulseGate);

					if ( neuroWorld->connect( lastEntity, pulseGate)) playSound( "GoodBud");
					else playSound( "BadBud");
				}
				else
				{
					playSound( "BadBud");
				}
			}
		}
	}
	else if(id == OIS::MB_Right)
	{
		m_bRMouseDown = false;
	}

	InjectOISMouseButton(false, id);

	return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::onLeftPressed(const OIS::MouseEvent &evt)
{
	Ogre::Entity* entity;

	float mx = (float)evt.state.X.abs / (float)evt.state.width;
	float my = (float)evt.state.Y.abs / (float)evt.state.height;

	if ( selectionManager->getLastNode() != NULL)
	{
		ac::es::EntityPtr node = selectionManager->getLastNode();
		Ogre::Entity* selectedObject;

		selectedObject = neuroWorld->getConstructConnectorUnderPoint( mx, my);

		if ( selectedObject != NULL && haveSameNode( node, getEntityPtr( selectedObject)))
		{
			if ( currentConnector != NULL) currentConnector->getParentSceneNode()->showBoundingBox(false);
			currentConnector = selectedObject;
			currentConnector->getParentSceneNode()->showBoundingBox(true);

			selectionManager->popUntilNode();
			selectionManager->pushResourceBud( selectedObject);
			playSound( "SelectObject");

			np::GraphicComponent* graphic = getEntityPtr(selectedObject)->getComponent<np::GraphicComponent>();
			bool hasPulseGate = getEntityPtr(selectedObject)->containsComponent<np::PulseGateComponent>();

			connectionPreview->updateSource( graphic->node->_getDerivedPosition());
			if ( !hasPulseGate) connectionPreview->show();

			return;
		}
		else if ( currentConnector != NULL)
		{
			if ( currentConnector->getParentSceneNode() != NULL) currentConnector->getParentSceneNode()->showBoundingBox(false);
			currentConnector = NULL;
		}

		selectedObject = neuroWorld->getNearestConstructConnectionFromPoint( mx, my);

		if ( selectedObject != NULL && haveSameNode( node, getEntityPtr( selectedObject)))
		{
			selectionManager->popUntilNode();
			selectionManager->pushConstructConnection( selectedObject);

			return;
		}

		selectedObject = neuroWorld->getConstructUnderPoint( mx, my);

		if ( selectedObject != NULL && haveSameNode( node, getEntityPtr( selectedObject)))
		{
			if ( currentConstruct != NULL) currentConstruct->getParentSceneNode()->showBoundingBox(false);
			currentConstruct = selectedObject;
			currentConstruct->getParentSceneNode()->showBoundingBox(true);

			selectionManager->popUntilNode();
			selectionManager->pushConstruct( selectedObject);
			playSound( "SelectObject");

			return;
		}
		else if ( currentConstruct != NULL)
		{
			currentConstruct->getParentSceneNode()->showBoundingBox(false);
			currentConstruct = NULL;
		}
	}

	Ogre::Entity* newNode = neuroWorld->getNodeUnderPoint( mx, my);

	if ( newNode != NULL && currentNode != newNode)
	{
		onNodeSelected( newNode);
		currentNode = newNode;

		selectionManager->popNode();
		selectionManager->pushNode( newNode);
		playSound( "SelectObject");
	}

	selectionManager->popUntilNode();
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::moveCamera()
{
	neuroWorld->getCameraTransform()->position += m_TranslateVector;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::getInput()
{
	if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_A))
		m_TranslateVector.x = -m_MoveScale;

	if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_D))
		m_TranslateVector.x = m_MoveScale;

	if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_W))
		m_TranslateVector.z = -m_MoveScale;

	if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_S))
		m_TranslateVector.z = m_MoveScale;

	if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_R))
		m_TranslateRelativeVector.z = m_MoveScale;

	if(OgreFramework::getSingletonPtr()->m_pKeyboard->isKeyDown(OIS::KC_F))
		m_TranslateRelativeVector.z = -m_MoveScale;

	m_TranslateVector -= neuroWorld->getCameraTransform()->rotation * m_TranslateRelativeVector;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::update(double timeSinceLastFrame)
{
	m_FrameEvent.timeSinceLastFrame = timeSinceLastFrame;

	np::TransformComponent* st = nodeSelector->getComponent<np::TransformComponent>();
	st->rotation = st->rotation * Ogre::Quaternion( Ogre::Degree( -0.2), Ogre::Vector3::UNIT_Y);

	CEGUI::System::getSingleton().injectTimePulse(timeSinceLastFrame / 1000.0);

	if(m_bQuit == true)
	{
		popAppState();
		return;
	}

	m_TranslateVector = Vector3::ZERO;
	m_TranslateRelativeVector = Vector3::ZERO;

	m_MoveScale = m_MoveSpeed * timeSinceLastFrame;

	neuroWorld->update( timeSinceLastFrame);

	CEGUI::String debugText = "";

	lastSelected = selectionManager->getLast();
	if ( lastSelected != NULL)
	{
		ac::es::EntityPtr entity = getEntityPtr( lastSelected);

		if ( entity != NULL)
		{
			if ( entity->containsComponent<np::BufferComponent>() )
			{
				debugText += CEGUI::String( "raw energy:      " + Ogre::StringConverter::toString( Ogre::Real( entity->getComponent<np::BufferComponent>()->getAmountOf( np::ResourceManager::getSingletonPtr()->getType("RawEnergy"))))) + "\n";
				debugText += CEGUI::String( "sexy energy:      " + Ogre::StringConverter::toString( Ogre::Real( entity->getComponent<np::BufferComponent>()->getAmountOf( np::ResourceManager::getSingletonPtr()->getType("SexyEnergy"))))) + "\n";
			}
			if( entity->containsComponent<np::NodeComponent>())
			{
				debugText += CEGUI::String( "heat:        " + Ogre::StringConverter::toString( Ogre::Real( entity->getComponent<np::BufferComponent>()->getAmountOf( np::ResourceManager::getSingletonPtr()->getType("Heat"))))) + "\n";
				debugText += CEGUI::String( "temperature: " + Ogre::StringConverter::toString( Ogre::Real( entity->getComponent<np::NodeComponent>()->temperature))) + "\n";
			}
			if( entity->containsComponent<np::HubComponent>())
				debugText += CEGUI::String( "health:      " + Ogre::StringConverter::toString( Ogre::Real( entity->getComponent<np::HubComponent>()->health))) + "\n";
		}
	}
	debug_txt->setText( debugText);


	//Gui
	if ( selectionManager->getLast() != NULL)
	{
		guiManager->setEntity( getEntityPtr( selectionManager->getLast()));
	}
	else
	{
		guiManager->setEntity( NULL);
	}

	OgreOggSound::OgreOggSoundManager::getSingletonPtr()->getListener()->setPosition( neuroWorld->getCameraTransform()->position);

	getInput();
	moveCamera();
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::buildGUI()
{
	CEGUI::System::getSingleton().setGUISheet( sheet);
	CEGUI::System::getSingleton().signalRedraw();
}

ac::es::EntityPtr GameState::getEntityPtr( Ogre::Entity* entity)
{
	const Ogre::Any& entityAny = entity->getUserObjectBindings().getUserAny("Entity");
	if ( !entityAny.isEmpty())
	{
		return entityAny.get<ac::es::EntityPtr>();
	}

	return NULL;
}

void GameState::onNodeSelected( Ogre::Entity* node)
{
	ac::es::EntityPtr previousNode	= selectionManager->getLastNode();
	ac::es::EntityPtr newNode		= getEntityPtr( node);

	if ( previousNode != NULL &&  previousNode->containsComponent<np::HubComponent>()) previousNode->getComponent<np::HubComponent>()->hideStructures();

	np::TransformComponent* transform = newNode->getComponent<np::TransformComponent>();
	neuroWorld->getCameraTransform()->position = transform->position + neuroWorld->cameraOffset;

	setNodeSelector( newNode);

	if ( newNode->containsComponent<np::HubComponent>()) newNode->getComponent<np::HubComponent>()->showStructures();
}

void GameState::onConstructSelected( Ogre::Entity* construct)
{

}

void GameState::onConnectorSelected( Ogre::Entity* connector)
{

}

//CEGUI Input

void GameState::InjectOISKey(bool bButtonDown, OIS::KeyEvent inKey)
{
	if (bButtonDown)
	{
		CEGUI::System::getSingleton().injectKeyDown(inKey.key);
		CEGUI::System::getSingleton().injectChar(inKey.text);
	}
	else
	{
		CEGUI::System::getSingleton().injectKeyUp(inKey.key);
	}
}

bool GameState::InjectOISMouseButton(bool bButtonDown, OIS::MouseButtonID inButton)
{
	if (bButtonDown == true)
	{
		switch (inButton)
		{
		case OIS::MB_Left:
			return CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::LeftButton);
			break;
		case OIS::MB_Middle:
			return CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::MiddleButton);
			break;
		case OIS::MB_Right:
			return CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::RightButton);
			break;
		case OIS::MB_Button3:
			return CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::X1Button);
			break;
		case OIS::MB_Button4:
			return CEGUI::System::getSingleton().injectMouseButtonDown(CEGUI::X2Button);
			break;
		default:	
			return false;
			break;

		}
	}
	else // bButtonDown = false
	{
		switch (inButton)
		{
		case OIS::MB_Left:
			return CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::LeftButton);
			break;
		case OIS::MB_Middle:
			return CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::MiddleButton);
			break;
		case OIS::MB_Right:
			return CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::RightButton);
			break;
		case OIS::MB_Button3:
			return CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::X1Button);
			break;
		case OIS::MB_Button4:
			return CEGUI::System::getSingleton().injectMouseButtonUp(CEGUI::X2Button);
			break;
		default:	
			return false;
			break;
		}
	}
	return false;

}

bool GameState::haveSameNode( ac::es::EntityPtr node, ac::es::EntityPtr e )
{
	if ( e->containsComponent<np::ResourceInputComponent>()) return node == e->getComponent<np::ResourceInputComponent>()->hub;
	else if ( e->containsComponent<np::ResourceOutputComponent>()) return node == e->getComponent<np::ResourceOutputComponent>()->hub;
	else if ( e->containsComponent<np::ConstructConnectionComponent>()) return node == e->getComponent<np::ConstructConnectionComponent>()->hub;
	else if ( e->containsComponent<np::ConstructComponent>()) return node == e->getComponent<np::ConstructComponent>()->hub;

	return false;
}

void GameState::playSound( Ogre::String soundId )
{
	OgreOggSound::OgreOggISound* sound = OgreOggSound::OgreOggSoundManager::getSingletonPtr()->getSound( soundId);
	sound->setPlayPosition(0.0);
	sound->play();
}

void GameState::setNodeSelector( ac::es::EntityPtr node )
{
	np::TransformComponent* st = nodeSelector->getComponent<np::TransformComponent>();
	np::GraphicComponent* graphic = nodeSelector->getComponent<np::GraphicComponent>();
	np::TransformComponent* nt = node->getComponent<np::TransformComponent>();

	st->position = nt->position;
	graphic->show();
}
