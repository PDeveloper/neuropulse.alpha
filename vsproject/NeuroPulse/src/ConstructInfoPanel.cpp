#include "ConstructInfoPanel.h"

#include <ConstructComponent.h>
#include <Construct.h>
#include <AdvancedOgreFramework.hpp>


np::ConstructInfoPanel::ConstructInfoPanel(CEGUI::WindowManager* wmgr)
{
	currentConstruct = NULL;

	this->wmgr = wmgr;

	sheet = wmgr->createWindow("TaharezLook/FrameWindow", "ConstructInfoPanel/Info");

	sheet->setSize( CEGUI::UVector2( CEGUI::UDim( 0, 220), CEGUI::UDim( 0, 300)));
	//sheet->setPosition(CEGUI::UVector2( CEGUI::UDim( 1/3, 0), CEGUI::UDim( 0.0, 0)));
	sheet->setText("Construct");
	sheet->setAlpha( 0.5);

	
	nameText = wmgr->createWindow("TaharezLook/StaticText", "ConstructInfoPanel/NameText");
	nameText->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.0, 0), CEGUI::UDim( 0, 0)));
	nameText->setSize(CEGUI::UVector2(CEGUI::UDim(0, 200), CEGUI::UDim(0, 60)));
	nameText->setFont("Title");
	//nameText->setAlpha( 0.5);
	sheet->addChildWindow(nameText);


	propertyPanel = new PropertyPanel(wmgr, "ConstructInfo");
	sheet->addChildWindow(propertyPanel->sheet);
	propertyPanel->sheet->setPosition(CEGUI::UVector2( CEGUI::UDim( 0.0, 0), CEGUI::UDim( 0, 100)));
	propertyPanel->sheet->setSize(CEGUI::UVector2( CEGUI::UDim( 0.0, 200), CEGUI::UDim( 0, 300)));

	
	/*
	descriptionText = wmgr->createWindow("TaharezLook/StaticText", "ConstructInfoPanel/DescriptionText");
	descriptionText->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.0, 0), CEGUI::UDim( 0.6, 0)));
	descriptionText->setSize(CEGUI::UVector2(CEGUI::UDim(0.5, 0), CEGUI::UDim(0.2, 0)));
	descriptionText->setAlpha( 0.5);
	sheet->addChildWindow(descriptionText);
	*/
}


np::ConstructInfoPanel::~ConstructInfoPanel(void)
{
}

void np::ConstructInfoPanel::setConstruct( ac::es::EntityPtr construct )
{
	bool changed = this->currentConstruct != construct;

	

	this->currentConstruct = construct;
	

	if(changed)
	{
		//OgreFramework::getSingletonPtr()->m_pLog->logMessage("Bing bong");
		if ( construct != NULL)
		{
			np::ConstructComponent* constructComp = construct->getComponent<np::ConstructComponent>();
			if(constructComp != NULL)
			{
				if(constructComp->construct != NULL)
				{
					nameText->setText(constructComp->construct->getName());

					//OgreFramework::getSingletonPtr()->m_pLog->logMessage("Bing "+Ogre::StringConverter::toString(constructComp->construct->getOn()));

					propertyPanel->setInterface((constructComp->construct->componentInterface));

				}
			}
		}
	}

	update();
}

void np::ConstructInfoPanel::update()
{
	if ( currentConstruct != NULL)
	{
		np::ConstructComponent* constructComp = currentConstruct->getComponent<np::ConstructComponent>();

		if(constructComp != NULL)
		{
			sheet->setVisible(true);

			if(constructComp->construct != NULL)
			{
				nameText->setText(constructComp->construct->getName());

				//constructComp->construct->setOn(onOffCheckBox->isSelected());

				propertyPanel->setInterface(constructComp->construct->componentInterface);
				
				sheet->setVisible(true);
				
			}
			else
			{
				sheet->setVisible(false);
			}
		}
		else
		{
			sheet->setVisible(false);
		}
	}
	else
	{
		sheet->setVisible(false);
	}
		

}


