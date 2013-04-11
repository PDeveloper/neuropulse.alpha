#include "ConstructInfoPanel.h"

#include <ConstructComponent.h>
#include <Construct.h>
#include <AdvancedOgreFramework.hpp>


np::ConstructInfoPanel::ConstructInfoPanel(CEGUI::WindowManager* wmgr)
{
	currentConstruct = NULL;

	this->wmgr = wmgr;

	sheet = wmgr->createWindow("TaharezLook/FrameWindow", "ConstructInfoPanel/Main");


	sheet->setSize( CEGUI::UVector2( CEGUI::UDim( 0, 220), CEGUI::UDim( 0, 300)));
	//sheet->setPosition(CEGUI::UVector2( CEGUI::UDim( 1/3, 0), CEGUI::UDim( 0.0, 0)));
	sheet->setText("Construct");
	sheet->setAlpha( 0.5);

	nameText = wmgr->createWindow("TaharezLook/StaticText", "ConstructInfoPanel/NameText");
	nameText->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.0, 0), CEGUI::UDim( 0, 0)));
	nameText->setSize(CEGUI::UVector2(CEGUI::UDim(0, 200), CEGUI::UDim(0, 50)));
	//nameText->setAlpha( 0.5);
	sheet->addChildWindow(nameText);

	onOffCheckBox = static_cast<CEGUI::Checkbox*>(wmgr->createWindow("TaharezLook/Checkbox", "ConstructInfoPanel/OnOffCheckbox"));
	onOffCheckBox->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.0, 0), CEGUI::UDim( 0, 50)));;
	onOffCheckBox->setSize(CEGUI::UVector2(CEGUI::UDim(0, 200), CEGUI::UDim(0, 50)));;
	onOffCheckBox->setText("On/Off");
	onOffCheckBox->subscribeEvent(CEGUI::Checkbox::EventCheckStateChanged, CEGUI::Event::Subscriber(&ConstructInfoPanel::onCheckStateChanged, this));
	//onOffCheckBox->setSelected(true);
	sheet->addChildWindow(onOffCheckBox);
	//onOffCheckBox->setSelected(true);


	propertyPanel = new PropertyPanel(wmgr);
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

					onOffCheckBox->setSelected(constructComp->construct->getOn());

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

			if(constructComp->construct != NULL)
			{
				nameText->setText(constructComp->construct->getName());

				//constructComp->construct->setOn(onOffCheckBox->isSelected());
				
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

bool np::ConstructInfoPanel::onCheckStateChanged( const CEGUI::EventArgs &e )
{
	//OgreFramework::getSingletonPtr()->m_pLog->logMessage("Bing "+Ogre::StringConverter::toString(onOffCheckBox->isSelected()));


	if ( currentConstruct != NULL)
	{
		np::ConstructComponent* constructComp = currentConstruct->getComponent<np::ConstructComponent>();

		if(constructComp != NULL)
		{


			if(constructComp->construct != NULL)
			{
				//OgreFramework::getSingletonPtr()->m_pLog->logMessage("Bang "+Ogre::StringConverter::toString(constructComp->construct->getOn()));


				constructComp->construct->setOn(onOffCheckBox->isSelected());

				//OgreFramework::getSingletonPtr()->m_pLog->logMessage("Bong "+Ogre::StringConverter::toString(constructComp->construct->getOn()));


				
			}
		}
	}

	return true;
}
