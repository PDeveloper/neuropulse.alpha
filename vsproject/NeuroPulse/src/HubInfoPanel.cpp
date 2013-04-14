#include "HubInfoPanel.h"
#include <HubComponent.h>
#include <AdvancedOgreFramework.hpp>
#include <OutputDoubleProperty.h>

np::HubInfoPanel::HubInfoPanel(CEGUI::WindowManager* wmgr)
{
	this->wmgr = wmgr;


	currentHub = NULL;

	sheet = wmgr->createWindow("DefaultWindow", "HubInfo/Sheet");
	sheet->setSize( CEGUI::UVector2( CEGUI::UDim( 0.0, 200), CEGUI::UDim( 0.0, 100)));
	sheet->setPosition(CEGUI::UVector2( CEGUI::UDim( 0.0, 0), CEGUI::UDim( 0.0, 100)));
	//sheet->setText("Hub");

	/*
	healthText = wmgr->createWindow("TaharezLook/StaticText", "HubInfoPanel/HealthText");
	healthText->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.0, 0), CEGUI::UDim( 0, 0)));
	healthText->setSize(CEGUI::UVector2(CEGUI::UDim(0, 200), CEGUI::UDim(0, 50)));
	healthText->setFont("Text");
	//healthText->setAlpha( 0.5);
	sheet->addChildWindow(healthText);
	*/

	componentInterface = new np::ComponentInterface();
	componentInterface->addProperty(new OutputDoubleProperty("Health", &health));
	

	propertyPanel = new np::PropertyPanel(wmgr, "Hub");
	propertyPanel->setPosition(CEGUI::UVector2( CEGUI::UDim(0, 0), CEGUI::UDim( 0.0, 0)));
	sheet->addChildWindow(propertyPanel->sheet);
	propertyPanel->setInterface(componentInterface);
}


np::HubInfoPanel::~HubInfoPanel(void)
{
}

void np::HubInfoPanel::setHub( ac::es::EntityPtr hub )
{
	this->currentHub = hub;

	update();
}

void np::HubInfoPanel::update()
{
	np::HubComponent* hub = currentHub->getComponent<np::HubComponent>();

	if ( hub != NULL)
	{
		sheet->setVisible(true);

		//healthText->setText("Hub Health: "+Ogre::StringConverter::toString( Ogre::Real(hub->health)));
		health = hub->health;

		propertyPanel->update();
	}
	else
	{
		sheet->setVisible(false);
	}
}
