#include <CEGUI.h>
#include <ac/es.h>
#include <PropertyPanel.h>
#include <ConstructBuildMenu.h>

#pragma once
namespace np
{
	class NotificationBar
	{
	public:

		CEGUI::Window* sheet;

		CEGUI::Window* constructInfoSheet;
		CEGUI::WindowManager* wmgr;

		CEGUI::Window* textWindow;
		std::string text;
		
		void setText(std::string newText);
		void update();

		void show();
		void hide();

		void setPosition(CEGUI::UVector2 positionVector)
		{
			sheet->setPosition(positionVector);
		}

		NotificationBar(CEGUI::WindowManager* wmgr);
		~NotificationBar(void);

	private:

	};
}
