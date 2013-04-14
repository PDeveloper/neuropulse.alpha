#include <BufferInfoPanel.h>
#include <BufferComponent.h>
#include <AdvancedOgreFramework.hpp>
#include <OutputDoubleProperty.h>

np::BufferInfoPanel::BufferInfoPanel( CEGUI::WindowManager* wmgr )
{
	currentBuffer = NULL;

	this->wmgr = wmgr;

	sheet = wmgr->createWindow("DefaultWindow", "BufferInfoPanel/Main");

	sheet->setSize( CEGUI::UVector2( CEGUI::UDim( 0.0, 200), CEGUI::UDim( 0.0, 200)));
	sheet->setPosition(CEGUI::UVector2( CEGUI::UDim( 0, 0), CEGUI::UDim( 0.0, 0)));

	/*
	resourceText = wmgr->createWindow("TaharezLook/StaticText", "BufferInfoPanel/ResourceText");
	resourceText->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.0, 0), CEGUI::UDim( 0, 0)));
	resourceText->setSize(CEGUI::UVector2(CEGUI::UDim(0, 200), CEGUI::UDim(0, 200)));
	resourceText->setFont("Text");
	//resourceText->setAlpha( 0.5);
	sheet->addChildWindow(resourceText);
	*/

	componentInterface = new np::ComponentInterface();


	propertyPanel = new np::PropertyPanel(wmgr, "Buffer");
	propertyPanel->setPosition(CEGUI::UVector2( CEGUI::UDim(0, 0), CEGUI::UDim( 0.0, 0)));
	sheet->addChildWindow(propertyPanel->sheet);
	propertyPanel->setInterface(componentInterface);
}

np::BufferInfoPanel::~BufferInfoPanel( void )
{

}

void np::BufferInfoPanel::setBuffer( ac::es::EntityPtr buffer )
{
	if(this->currentBuffer != buffer)
	{
		if(buffer != NULL)
		{
			np::BufferComponent* bufferComp = buffer->getComponent<np::BufferComponent>();

			if(bufferComp != NULL)
			{
				np::ResourceManager* rm = np::ResourceManager::getSingletonPtr();

				std::vector<np::ResourceType*> types = rm->getTypes(&(bufferComp->getTypes()));

				//resourceText->setText("");

				//resourceText->setSize(CEGUI::UVector2(CEGUI::UDim(0, 200), CEGUI::UDim(0, types.size()*50)));

				amounts = new std::hash_map<std::string, double>();
				componentInterface = new np::ComponentInterface();

				for(int i=0; i<types.size(); i++)
				{
					(*amounts)[types.at(i)->name()] = bufferComp->getAmountOf(types.at(i));

					componentInterface->addProperty(new OutputDoubleProperty(types.at(i)->name(), &((*amounts)[types.at(i)->name()])));

					//resourceText->appendText(types.at(i)->name()+": "+Ogre::StringConverter::toString( Ogre::Real( buffer->getAmountOf(types.at(i))))+"\n");
				}

				propertyPanel->setInterface(componentInterface);

			}
		}
	}

	this->currentBuffer = buffer;

	update();
}

void np::BufferInfoPanel::update()
{
	if(currentBuffer != NULL)
	{
		np::BufferComponent* buffer = currentBuffer->getComponent<np::BufferComponent>();

		if(buffer != NULL)
		{
			np::ResourceManager* rm = np::ResourceManager::getSingletonPtr();

			std::vector<np::ResourceType*> types = rm->getTypes(&(buffer->getTypes()));

			//resourceText->setText("");

			//resourceText->setSize(CEGUI::UVector2(CEGUI::UDim(0, 200), CEGUI::UDim(0, types.size()*50)));

			amounts = new std::hash_map<std::string, double>();
			componentInterface = new np::ComponentInterface();

			for(int i=0; i<types.size(); i++)
			{
				(*amounts)[types.at(i)->name()] = buffer->getAmountOf(types.at(i));

				
				//resourceText->appendText(types.at(i)->name()+": "+Ogre::StringConverter::toString( Ogre::Real( buffer->getAmountOf(types.at(i))))+"\n");
			}

			sheet->setSize( CEGUI::UVector2( CEGUI::UDim( 0.0, 200), CEGUI::UDim( 0.0, 50*types.size())));

			propertyPanel->update();

		}
	}
	else
	{

	}
}
