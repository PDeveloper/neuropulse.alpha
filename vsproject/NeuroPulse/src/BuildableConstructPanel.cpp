#include "BuildableConstructPanel.h"
#include <ConstructComponent.h>
#include <ConstructBuildMenu.h>
#include <AdvancedOgreFramework.hpp>

np::BuildableConstructPanel::BuildableConstructPanel( CEGUI::WindowManager* wmgr, np::Construct* construct )
{
	this->construct = construct;

	this->wmgr = wmgr;

	this->entity = NULL;

	if(construct != NULL)
	{
		sheet = wmgr->createWindow("DefaultWindow", construct->getName() + "BuildMenu/Main");
		sheet->setSize(CEGUI::UVector2(CEGUI::UDim(0, 200), CEGUI::UDim(0, 100)));

		

		nameText = wmgr->createWindow("TaharezLook/StaticText", construct->getName() + "BuildMenu/NameText");
		nameText->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.0, 0), CEGUI::UDim( 0, 0)));
		nameText->setSize(CEGUI::UVector2(CEGUI::UDim(0, 200), CEGUI::UDim(0, 40)));
		nameText->setText(construct->getName());
		sheet->addChildWindow(nameText);

	
		descriptionText = wmgr->createWindow("TaharezLook/StaticText", construct->getName() + "BuildMenu/DescriptionText");
		descriptionText->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.0, 0), CEGUI::UDim( 0, 40)));
		descriptionText->setSize(CEGUI::UVector2(CEGUI::UDim(0, 200), CEGUI::UDim(0, 40)));
		descriptionText->setText(construct->getDescription());
		sheet->addChildWindow(descriptionText);

		buildButton = static_cast<CEGUI::PushButton*>( wmgr->createWindow("TaharezLook/Button", construct->getName() + "BuildMenu/BuildButton"));
		buildButton->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.0, 0), CEGUI::UDim( 0, 80)));
		buildButton->setSize(CEGUI::UVector2(CEGUI::UDim(0, 200), CEGUI::UDim(0, 20)));
		buildButton->setText("Build");
		buildButton->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&BuildableConstructPanel::onBuildButtonPressed, this));

		sheet->addChildWindow(buildButton);
	}
}

void np::BuildableConstructPanel::setEntity( ac::es::EntityPtr entity )
{
	this->entity = entity;
}

bool np::BuildableConstructPanel::onBuildButtonPressed( const CEGUI::EventArgs &e )
{
	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Bing");
	if(entity != NULL)
	{
		OgreFramework::getSingletonPtr()->m_pLog->logMessage("Bang");
		np::ConstructComponent* constructComp = entity->getComponent<np::ConstructComponent>();
		if(constructComp != NULL)
		{
			OgreFramework::getSingletonPtr()->m_pLog->logMessage("Bong");
			ConstructBuildMenu::objectFactory->setConstruct(entity, construct->getNewInstance());
		}
	}

	return true;
}


