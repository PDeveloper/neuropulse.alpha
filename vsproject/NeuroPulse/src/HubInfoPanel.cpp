#include "HubInfoPanel.h"


np::HubInfoPanel::HubInfoPanel(void)
{
	currentHub = NULL;

	CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
	sheet = wmgr.createWindow("DefaultWindow", "MainMenu/Sheet");

	sheet->setSize( CEGUI::UVector2( CEGUI::UDim( 0.0, 500), CEGUI::UDim( 0.0, 200)));
}


np::HubInfoPanel::~HubInfoPanel(void)
{
}

void np::HubInfoPanel::setHub( ac::es::EntityPtr hub )
{
	this->currentHub = hub;
}

void np::HubInfoPanel::update()
{
	if ( currentHub != NULL)
	{

	}
	else
	{

	}
}
