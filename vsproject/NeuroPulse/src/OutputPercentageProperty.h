#include <string>
#include <stdio.h>
#include <stdarg.h>
#include <ComponentProperty.h>
#include <AdvancedOgreFramework.hpp>

#pragma once
namespace np
{
	class OutputPercentageProperty : public ComponentProperty
	{
	public:
		OutputPercentageProperty(std::string name, double* value)
		{
			sheet = NULL;

			this->name = name;
			this->value = value;			
		}

		std::string type()
		{
			return "OutputDouble";
		}

		CEGUI::Window* getInitializedSheet(CEGUI::WindowManager* wmgr)
		{
			this->wmgr = wmgr;


			this->wmgr = wmgr;
			sheet = wmgr->createWindow("DefaultWindow", name+"/Main");


			nameText = wmgr->createWindow("TaharezLook/StaticText", name+"/Title");
			nameText->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.0, 0), CEGUI::UDim( 0, 0)));
			nameText->setSize(CEGUI::UVector2(CEGUI::UDim(0, 130), CEGUI::UDim(0, 30)));
			nameText->setText(name);
			nameText->setFont("Text");

			sheet->addChildWindow(nameText);

			valueText = wmgr->createWindow("TaharezLook/StaticText", name+"/Value");
			valueText->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.0, 130), CEGUI::UDim( 0, 0)));
			valueText->setSize(CEGUI::UVector2(CEGUI::UDim(0, 70), CEGUI::UDim(0, 30)));
			valueText->setFont("Text");

			sheet->addChildWindow(valueText);

			update();

			return sheet;
		}


		double* value;

		CEGUI::Window* nameText;
		CEGUI::Window* valueText;



		float getHeight()
		{
			return 30;
		}

		void update()
		{
			char buffer[256];  
			_snprintf_s(buffer, sizeof(buffer), "%.0f%%", *value*100.0);

			valueText->setText(buffer);
		}
	};
}