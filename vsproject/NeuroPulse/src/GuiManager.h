#include <CEGUI.h>
#include <ac/es.h>
#include <NodeInfoPanel.h>
#include <ConstructInfoPanel.h>
#include <BudInfoPanel.h>

#pragma once
namespace np
{
	class GuiManager
	{
	public:

		CEGUI::Window* sheet;
		CEGUI::WindowManager* wmgr;

		np::NodeInfoPanel* nodeInfoPanel;
		np::ConstructInfoPanel* constructInfoPanel;
		np::BudInfoPanel* budInfoPanel;

		ac::es::EntityPtr currentEntity;

		void setEntity( ac::es::EntityPtr entity);

		void update();

		void setPosition(CEGUI::UVector2 positionVector)
		{
			sheet->setPosition(positionVector);
		}

		GuiManager(CEGUI::WindowManager* wmgr);
		~GuiManager(void);
	};
}

