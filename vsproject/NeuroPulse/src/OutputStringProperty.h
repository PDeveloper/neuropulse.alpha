#include <string>
#include <ComponentProperty.h>
#include <AdvancedOgreFramework.hpp>

#pragma once
namespace np
{
	class OutputStringProperty : public ComponentProperty
	{
	public:
		OutputStringProperty(std::string uniqueId, std::string name, std::string* value)
		{
			sheet = NULL;

			this->uniqueId = uniqueId;
			this->name = name;
			this->value = value;			
		}

		std::string type()
		{
			return "String";
		}

		CEGUI::Window* getInitializedSheet(CEGUI::WindowManager* wmgr)
		{
			this->wmgr = wmgr;


			this->wmgr = wmgr;
			sheet = wmgr->createWindow("DefaultWindow", uniqueId+name+"/Main");


			text = wmgr->createWindow("TaharezLook/StaticText", uniqueId+name+"/Title");
			text->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.0, 0), CEGUI::UDim( 0, 0)));
			text->setSize(CEGUI::UVector2(CEGUI::UDim(0, 200), CEGUI::UDim(0, 30)));
			text->setText(name);
			text->setFont("Text");

			sheet->addChildWindow(text);
			



			return sheet;
		}


		std::string* value;

		CEGUI::Window* text;

		

		float getHeight()
		{
			return 30;
		}

		void update()
		{

		}
	};
}