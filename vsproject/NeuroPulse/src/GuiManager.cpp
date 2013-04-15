#include "GuiManager.h"

#include <ResourceInputComponent.h>
#include <ResourceOutputComponent.h>
#include <ConstructComponent.h>
#include <NodeComponent.h>


np::GuiManager::GuiManager( CEGUI::WindowManager* wmgr, float screenWidth, float screenHeight)
{
	this->wmgr = wmgr;
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;

	timeSinceLastUpdate = 0;

	currentEntity = NULL;
	

	if(! CEGUI::FontManager::getSingleton().isDefined( "DejaVuSans-10" ) )
			CEGUI::FontManager::getSingleton().createFreeTypeFont( "DejaVuSans-10", 10, true, "DejaVuSans.ttf", "Fonts" );
	CEGUI::System::getSingleton().setDefaultFont( "DejaVuSans-10" );

	if(! CEGUI::FontManager::getSingleton().isDefined( "Title" ) )
		CEGUI::FontManager::getSingleton().createFreeTypeFont( "Title", 14, true, "DejaVuSans.ttf", "Fonts");


	if(! CEGUI::FontManager::getSingleton().isDefined( "SmallText" ) )
		CEGUI::FontManager::getSingleton().createFreeTypeFont( "SmallText", 8, true, "DejaVuSans.ttf", "Fonts" );

	if(! CEGUI::FontManager::getSingleton().isDefined( "Text" ) )
		CEGUI::FontManager::getSingleton().createFreeTypeFont( "Text", 10, true, "DejaVuSans.ttf", "Fonts");
	
	CEGUI::System::getSingleton().setDefaultFont( "Title" );
	

	

	sheet = wmgr->createWindow( "DefaultWindow", "MainGuiSheet");
	//sheet->setSize( CEGUI::UVector2( CEGUI::UDim( 0, 10000), CEGUI::UDim( 0, 10000)));
	//sheet->setPosition(CEGUI::UVector2( CEGUI::UDim( 0, 0), CEGUI::UDim( 0, 0)));
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

	buildMenu = new ConstructBuildMenu(wmgr);
	buildMenu->setPosition(CEGUI::UVector2( CEGUI::UDim( 0, screenWidth - 220), CEGUI::UDim( 0, 0)));
	buildMenu->sheet->setSize(CEGUI::UVector2( CEGUI::UDim( 0, 220), CEGUI::UDim( 0, screenHeight)));
	sheet->addChildWindow(buildMenu->sheet);
	buildMenu->sheet->setVisible(false);

	notificationBar = new np::NotificationBar(wmgr);
	notificationBar->setPosition(CEGUI::UVector2( CEGUI::UDim( 0, 0), CEGUI::UDim( 0, screenHeight - 50)));
	notificationBar->sheet->setSize(CEGUI::UVector2( CEGUI::UDim( 0, screenWidth), CEGUI::UDim( 0, 50)));
	notificationBar->setText("Do you feel notified?");
	sheet->addChildWindow(notificationBar->sheet);
	notificationBar->show();

}


void np::GuiManager::setEntity( ac::es::EntityPtr entity )
{
	currentEntity = entity;
	
	if(currentEntity != entity)
	{
		timeSinceLastUpdate = GuiManager::UPDATE_INTERVAL;
		update(1);
	}
	
}

void np::GuiManager::update( float timePassed )
{

	timeSinceLastUpdate += timePassed;

	if (timeSinceLastUpdate > GuiManager::UPDATE_INTERVAL)
	{
		timeSinceLastUpdate = 0;
		if(currentEntity != NULL)
		{
			//If node
			if(currentEntity->containsComponent<np::NodeComponent>())
			{
				nodeInfoPanel->setNode(currentEntity);
				constructInfoPanel->setConstruct(NULL);
				budInfoPanel->setBud(NULL);

				buildMenu->setEntity(NULL);
			}
			//Construct
			else if(currentEntity->containsComponent<np::ConstructComponent>())
			{
				nodeInfoPanel->setNode(currentEntity->getComponent<np::ConstructComponent>()->parent);
				constructInfoPanel->setConstruct(currentEntity);
				budInfoPanel->setBud(NULL);

				buildMenu->setEntity(currentEntity);
			}
			//bud
			else if(currentEntity->containsComponent<np::ResourceInputComponent>())
			{
				nodeInfoPanel->setNode(currentEntity->getComponent<np::ResourceInputComponent>()->hub);
				constructInfoPanel->setConstruct(currentEntity->getComponent<np::ResourceInputComponent>()->parent);
				budInfoPanel->setBud(currentEntity);

				buildMenu->setEntity(NULL);

			}
			else if(currentEntity->containsComponent<np::ResourceOutputComponent>())
			{
				nodeInfoPanel->setNode(currentEntity->getComponent<np::ResourceOutputComponent>()->hub);
				constructInfoPanel->setConstruct(currentEntity->getComponent<np::ResourceOutputComponent>()->parent);
				budInfoPanel->setBud(currentEntity);

				buildMenu->setEntity(NULL);
			}
		}
		else
		{
			nodeInfoPanel->setNode(NULL);
			constructInfoPanel->setConstruct(NULL);
			budInfoPanel->setBud(NULL);

			buildMenu->setEntity(NULL);
		}
}
}

const float np::GuiManager::UPDATE_INTERVAL = 100;
