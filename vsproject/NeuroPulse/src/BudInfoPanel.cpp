#include <BudInfoPanel.h>
#include <ResourceInputComponent.h>
#include <ResourceOutputComponent.h>
#include <AdvancedOgreFramework.hpp>

np::BudInfoPanel::BudInfoPanel( CEGUI::WindowManager* wmgr )
{
	this->wmgr = wmgr;

	sheet = wmgr->createWindow("TaharezLook/FrameWindow", "BudInfoPanel/Main");


	sheet->setSize( CEGUI::UVector2( CEGUI::UDim( 0, 200), CEGUI::UDim( 0, 200)));
	sheet->setPosition(CEGUI::UVector2( CEGUI::UDim( 2/3, 0), CEGUI::UDim( 0.0, 0)));
	sheet->setAlpha( 0.5);

	typeText = wmgr->createWindow("TaharezLook/StaticText", "BudtInfoPanel/TypeText");
	typeText->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.0, 0), CEGUI::UDim( 0, 0)));
	typeText->setSize(CEGUI::UVector2(CEGUI::UDim(0.5, 0), CEGUI::UDim(0.2, 0)));
	typeText->setAlpha( 0.5);
	//sheet->addChildWindow(typeText);
	

	bufferInfo = new BufferInfoPanel(wmgr);
	sheet->addChildWindow(bufferInfo->sheet);
}

np::BudInfoPanel::~BudInfoPanel( void )
{

}

void np::BudInfoPanel::setBud( ac::es::EntityPtr bud )
{
	this->currentBud = bud;
	
	update();
}

void np::BudInfoPanel::update()
{
	if(currentBud != NULL)
	{
		
		np::ResourceInputComponent* input = currentBud->getComponent<np::ResourceInputComponent>();
		np::ResourceOutputComponent* output = currentBud->getComponent<np::ResourceOutputComponent>();

		bufferInfo->setBuffer(currentBud);

		sheet->setVisible(true);

		//Input
		if(input != NULL)
		{
			sheet->setText("Input");
		}
		//output
		else if(output != NULL)
		{
			sheet->setText("Output");
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

