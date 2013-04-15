#include <CEGUI.h>
#include <ac/es.h>
#include <PropertyPanel.h>
#include <ConstructBuildMenu.h>

#pragma once
namespace np
{
	class ConstructInfoPanel
	{
	public:

		
		CEGUI::Window* sheet;
		CEGUI::WindowManager* wmgr;

		CEGUI::Window* nameText;
		CEGUI::Window* descriptionText;
		
		
		PropertyPanel* propertyPanel;
		
		ac::es::EntityPtr currentConstruct;

		void setConstruct( ac::es::EntityPtr construct);
		void update();

		void setPosition(CEGUI::UVector2 positionVector)
		{
			sheet->setPosition(positionVector);
		}
		
		ConstructInfoPanel(CEGUI::WindowManager* wmgr);
		~ConstructInfoPanel(void);

	private:

	};
}
