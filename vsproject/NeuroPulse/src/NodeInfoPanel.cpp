#include "NodeInfoPanel.h"

np::NodeInfoPanel::NodeInfoPanel(void)
{
	currentNode = NULL;

	CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
	sheet = wmgr.createWindow("DefaultWindow", "MainMenu/Sheet");

	sheet->setSize( CEGUI::UVector2( CEGUI::UDim( 0.0, 500), CEGUI::UDim( 0.0, 200)));
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

	}
	else
	{
		
	}
}
