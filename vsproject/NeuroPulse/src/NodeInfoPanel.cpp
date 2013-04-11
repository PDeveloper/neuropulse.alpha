#include "NodeInfoPanel.h"
#include <HubComponent.h>
#include <NodeComponent.h>
#include <BufferComponent.h>
#include <AdvancedOgreFramework.hpp>

np::NodeInfoPanel::NodeInfoPanel(CEGUI::WindowManager* wmgr)
{
	this->wmgr = wmgr;

	currentNode = NULL;

	sheet = wmgr->createWindow("TaharezLook/FrameWindow", "NodeInfoPanel/Main");


	sheet->setSize( CEGUI::UVector2( CEGUI::UDim( 0, 220), CEGUI::UDim( 0, 300)));
	sheet->setPosition(CEGUI::UVector2( CEGUI::UDim(0, 0), CEGUI::UDim( 0.0, 0)));
	sheet->setText("Node");
	sheet->setAlpha( 0.5);

	energyText = wmgr->createWindow("TaharezLook/StaticText", "NodeInfoPanel/EnergyText");
	energyText->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.0, 0), CEGUI::UDim( 0.0, 0)));
	energyText->setSize(CEGUI::UVector2(CEGUI::UDim(0, 200), CEGUI::UDim(0, 50)));
	//energyText->setAlpha( 0.5);
	sheet->addChildWindow(energyText);

	temperatureText = wmgr->createWindow("TaharezLook/StaticText", "NodeInfoPanel/TemperatureText");
	temperatureText->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.0, 0), CEGUI::UDim( 0, 50)));
	temperatureText->setSize(CEGUI::UVector2(CEGUI::UDim(0, 200), CEGUI::UDim(0, 50)));
	//temperatureText->setAlpha( 0.5);
	sheet->addChildWindow(temperatureText);

	hubInfo = new np::HubInfoPanel(wmgr);

	sheet->addChildWindow(hubInfo->sheet);
}

np::NodeInfoPanel::~NodeInfoPanel(void)
{
}

void np::NodeInfoPanel::setNode( ac::es::EntityPtr node)
{
	this->currentNode = node;

	update();
}

void np::NodeInfoPanel::update()
{
	if ( currentNode != NULL)
	{
		np::NodeComponent* node = currentNode->getComponent<np::NodeComponent>();
		

		sheet->setVisible(true);

		energyText->setText("Energy: "+Ogre::StringConverter::toString( Ogre::Real( currentNode->getComponent<np::BufferComponent>()->getAmountOf( np::ResourceManager::getSingletonPtr()->getType("RawEnergy")))));

		temperatureText->setText("T: "+Ogre::StringConverter::toString( Ogre::Real(node->temperature)));

		hubInfo->setHub( currentNode);


	}
	else
	{
		sheet->setVisible(false);
	}
}
