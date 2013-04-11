#include <BufferInfoPanel.h>
#include <BufferComponent.h>
#include <AdvancedOgreFramework.hpp>

np::BufferInfoPanel::BufferInfoPanel( CEGUI::WindowManager* wmgr )
{
	this->wmgr = wmgr;

	sheet = wmgr->createWindow("DefaultWindow", "BufferInfoPanel/Main");

	sheet->setSize( CEGUI::UVector2( CEGUI::UDim( 0.0, 200), CEGUI::UDim( 0.0, 200)));
	sheet->setPosition(CEGUI::UVector2( CEGUI::UDim( 0, 0), CEGUI::UDim( 0.0, 0)));

	resourceText = wmgr->createWindow("TaharezLook/StaticText", "BufferInfoPanel/ResourceText");
	resourceText->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.0, 0), CEGUI::UDim( 0, 0)));
	resourceText->setSize(CEGUI::UVector2(CEGUI::UDim(0, 200), CEGUI::UDim(0, 200)));
	//resourceText->setAlpha( 0.5);
	sheet->addChildWindow(resourceText);
}

np::BufferInfoPanel::~BufferInfoPanel( void )
{

}

void np::BufferInfoPanel::setBuffer( ac::es::EntityPtr buffer )
{
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

			resourceText->setText("");

			resourceText->setSize(CEGUI::UVector2(CEGUI::UDim(0, 200), CEGUI::UDim(0, types.size()*50)));

			for(int i=0; i<types.size(); i++)
			{
				resourceText->appendText(types.at(i)->name()+": "+Ogre::StringConverter::toString( Ogre::Real( buffer->getAmountOf(types.at(i))))+"\n");
			}
		}
	}
	else
	{

	}
}
