#include "GuiManager.h"

#include <ResourceInputComponent.h>
#include <ResourceOutputComponent.h>
#include <ConstructComponent.h>
#include <NodeComponent.h>


np::GuiManager::GuiManager( CEGUI::WindowManager* wmgr)
{
	this->wmgr = wmgr;

	sheet = wmgr->createWindow( "DefaultWindow", "MainGuiSheet");
	//sheet->setSize( CEGUI::UVector2( CEGUI::UDim( 3/4, 0), CEGUI::UDim( 1/3, 0)));
	sheet->setPosition(CEGUI::UVector2( CEGUI::UDim( 0, 0), CEGUI::UDim( 0, 0)));
	sheet->setMousePassThroughEnabled(true);

	nodeInfoPanel = new np::NodeInfoPanel(wmgr);
	sheet->addChildWindow(nodeInfoPanel->sheet);
	nodeInfoPanel->setPosition(CEGUI::UVector2( CEGUI::UDim( 0, 0), CEGUI::UDim( 0, 0)));


	constructInfoPanel = new np::ConstructInfoPanel(wmgr);
	sheet->addChildWindow(constructInfoPanel->sheet);
	constructInfoPanel->setPosition(CEGUI::UVector2( CEGUI::UDim( 0, 220), CEGUI::UDim( 0, 0)));


	budInfoPanel = new np::BudInfoPanel(wmgr);
	sheet->addChildWindow(budInfoPanel->sheet);
	budInfoPanel->setPosition(CEGUI::UVector2( CEGUI::UDim( 0, 440), CEGUI::UDim( 0, 0)));

}


void np::GuiManager::setEntity( ac::es::EntityPtr entity )
{
	currentEntity = entity;
	

	if(currentEntity != NULL)
	{
		//If node
		if(currentEntity->containsComponent<np::NodeComponent>())
		{
			nodeInfoPanel->setNode(currentEntity);
			constructInfoPanel->setConstruct(NULL);
			budInfoPanel->setBud(NULL);
		}
		//Construct
		else if(currentEntity->containsComponent<np::ConstructComponent>())
		{
			nodeInfoPanel->setNode(currentEntity->getComponent<np::ConstructComponent>()->parent);
			constructInfoPanel->setConstruct(currentEntity);
			budInfoPanel->setBud(NULL);
		}
		//bud
		else if(currentEntity->containsComponent<np::ResourceInputComponent>())
		{
			nodeInfoPanel->setNode(currentEntity->getComponent<np::ResourceInputComponent>()->hub);
			constructInfoPanel->setConstruct(currentEntity->getComponent<np::ResourceInputComponent>()->parent);
			budInfoPanel->setBud(currentEntity);
		}
		else if(currentEntity->containsComponent<np::ResourceOutputComponent>())
		{
			nodeInfoPanel->setNode(currentEntity->getComponent<np::ResourceOutputComponent>()->hub);
			constructInfoPanel->setConstruct(currentEntity->getComponent<np::ResourceOutputComponent>()->parent);
			budInfoPanel->setBud(currentEntity);
		}
	}
	else
	{
		nodeInfoPanel->setNode(NULL);
		constructInfoPanel->setConstruct(NULL);
		budInfoPanel->setBud(NULL);
	}
}
