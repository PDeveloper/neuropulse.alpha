#include "ConstructBuildMenu.h"
#include <vector>
#include <AdvancedOgreFramework.hpp>
#include <RefineryConstructionConstruct.h>
#include <SexyEnergyBufferConstruction.h>

std::vector<np::Construct*>* np::ConstructBuildMenu::buildableConstructs = new std::vector<np::Construct*>();
np::GameObjectFactory* np::ConstructBuildMenu::objectFactory = NULL;

np::ConstructBuildMenu::ConstructBuildMenu( CEGUI::WindowManager* wmgr )
{
	


	this->wmgr = wmgr;

	panels = new std::vector<np::BuildableConstructPanel*>();

	sheet = wmgr->createWindow("TaharezLook/FrameWindow", "BuildMenu/Main");
	
	sheet->setText("Build Menu");
	sheet->setAlpha( 0.5);

	update();
}

void np::ConstructBuildMenu::setEntity( ac::es::EntityPtr entity )
{
	this->entity = entity;

	for(int i=0; i<panels->size(); i++)
	{
		panels->at(i)->setEntity(entity);
	}
}

void np::ConstructBuildMenu::update()
{
	//Remove old

	for(int i=0; i<panels->size(); i++)
	{
		sheet->removeChildWindow(panels->at(i)->sheet);
		panels->at(i)->sheet->destroy();

	}

	panels = new std::vector<np::BuildableConstructPanel*>();


	//Add new
	float height = 0;

	//OgreFramework::getSingletonPtr()->m_pLog->logMessage("Bing "+Ogre::StringConverter::toString(onOffCheckBox->isSelected()));
	
	for(int i=0; i<np::ConstructBuildMenu::buildableConstructs->size(); i++)
	{
		BuildableConstructPanel* panel = new BuildableConstructPanel(wmgr, np::ConstructBuildMenu::buildableConstructs->at(i));
		panels->push_back(panel);
		

		sheet->addChildWindow(panel->sheet);

		panel->sheet->setPosition(CEGUI::UVector2(CEGUI::UDim(0, 0), CEGUI::UDim(0, height)));

		

		height+=panel->getHeight();

		
	}

	sheet->setSize(CEGUI::UVector2(CEGUI::UDim(0, 220), CEGUI::UDim(0, height+500)));
}
