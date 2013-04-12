#include <CEGUI.h>
#include <ac/es.h>

#pragma once
namespace np
{
	class HubInfoPanel
	{
	public:

		CEGUI::Window* sheet;
		CEGUI::WindowManager* wmgr;

		CEGUI::Window* healthText;

		ac::es::EntityPtr currentHub;

		void setHub( ac::es::EntityPtr hub);

		void update();

		void setPosition(CEGUI::UVector2 positionVector)
		{
			sheet->setPosition(positionVector);
		}

		HubInfoPanel(CEGUI::WindowManager* wmgr);
		~HubInfoPanel(void);
	};
}

