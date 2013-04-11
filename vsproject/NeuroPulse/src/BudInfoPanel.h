#include <CEGUI.h>
#include <ac/es.h>
#include <BufferInfoPanel.h>

#pragma once
namespace np
{
	class BudInfoPanel
	{
	public:

		CEGUI::Window* sheet;
		CEGUI::WindowManager* wmgr;

		BufferInfoPanel* bufferInfo;

		CEGUI::Window* typeText;

		ac::es::EntityPtr currentBud;

		void setBud( ac::es::EntityPtr bud);
		void update();

		void setPosition(CEGUI::UVector2 positionVector)
		{
			sheet->setPosition(positionVector);
		}

		BudInfoPanel(CEGUI::WindowManager* wmgr);
		~BudInfoPanel(void);

	private:

	};
}
