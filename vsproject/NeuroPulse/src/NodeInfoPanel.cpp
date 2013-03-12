#include "NodeInfoPanel.h"
#include <HubComponent.h>

np::NodeInfoPanel::NodeInfoPanel(void)
{
	currentNode = NULL;

	CEGUI::WindowManager &wmgr = CEGUI::WindowManager::getSingleton();
	sheet = wmgr.createWindow("DefaultWindow", "NodeInfoPanel/Main");

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
		np::HubComponent* hub = currentNode->getComponent<np::HubComponent>();

		if ( hub != NULL)
		{
			hubInfo->setHub( currentNode);

			if ( hubInfo->sheet->getParent() != sheet) sheet->addChildWindow( hubInfo->sheet);
		}
		else
		{
			if ( hubInfo->sheet->getParent() == sheet) sheet->removeChildWindow( hubInfo->sheet->getID());
		}

	}
	else
	{
		
	}
}
