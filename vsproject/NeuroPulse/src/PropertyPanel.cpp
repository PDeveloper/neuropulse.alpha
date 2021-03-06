#include <PropertyPanel.h>
#include <ComponentProperty.h>
#include <AdvancedOgreFramework.hpp>

np::PropertyPanel::PropertyPanel( CEGUI::WindowManager* wmgr, std::string name)
{
	currentInterface = NULL;

	this->name = name;

	this->wmgr = wmgr;

	this->currentInterface = currentInterface;

	sheet = wmgr->createWindow("DefaultWindow", name+"PropertyPanel/Main");
	
}

void np::PropertyPanel::setInterface( np::ComponentInterface* newInterface )
{
	
	if(this->currentInterface != newInterface)
	{
		//Remove old
		if(this->currentInterface != NULL)
		{
			std::vector<np::ComponentProperty*>* properties = this->currentInterface->properties;
			for(int i=0; i<properties->size(); i++)
			{
				
				sheet->removeChildWindow(properties->at(i)->sheet->getName());
				properties->at(i)->unload();
			}
		}

		this->currentInterface = newInterface;

		//Add new
		if(this->currentInterface != NULL)
		{
			sheet->setSize(CEGUI::UVector2( CEGUI::UDim( 0.0, 1000), CEGUI::UDim( 0, 1000)));

			std::vector<np::ComponentProperty*>* properties = this->currentInterface->properties;

			float height = 0;

			for(int i=0; i<properties->size(); i++)			
			{
				//OgreFramework::getSingletonPtr()->m_pLog->logMessage("Bing bong");
				ComponentProperty* prop = properties->at(i);

				sheet->addChildWindow(prop->getInitializedSheet(wmgr));

				properties->at(i)->sheet->setPosition(CEGUI::UVector2( CEGUI::UDim( 0.0, 0), CEGUI::UDim( 0, height)));

				properties->at(i)->sheet->setSize(CEGUI::UVector2( CEGUI::UDim( 0.0, 200), CEGUI::UDim( 0, prop->getHeight())));

				

				height+=prop->getHeight();
			}

			sheet->setSize(CEGUI::UVector2( CEGUI::UDim( 0.0, 220), CEGUI::UDim( 0, height)));
		}

	}
	else
	{
		update();
	}
	

	


}

void np::PropertyPanel::update()
{
	if(this->currentInterface != NULL)
	{
		std::vector<np::ComponentProperty*>* properties = this->currentInterface->properties;
		for(int i=0; i<properties->size(); i++)
		{

			properties->at(i)->update();
		}
	}
}
