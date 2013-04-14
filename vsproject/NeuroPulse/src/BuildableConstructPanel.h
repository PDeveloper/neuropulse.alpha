#include <CEGUI.h>
#include <ac/es.h>
#include <PropertyPanel.h>
#include <Construct.h>
#include <GameObjectFactory.h>

#pragma once
namespace np
{
	class BuildableConstructPanel
	{
	public:

		
		CEGUI::Window* sheet;
		CEGUI::WindowManager* wmgr;

		CEGUI::Window* nameText;
		CEGUI::Window* descriptionText;
		CEGUI::PushButton* buildButton;

		ac::es::EntityPtr entity;
		np::Construct* construct;

		void setEntity( ac::es::EntityPtr entity);
		void update();

		void setPosition(CEGUI::UVector2 positionVector)
		{
			sheet->setPosition(positionVector);
		}

		BuildableConstructPanel(CEGUI::WindowManager* wmgr, np::Construct* construct);
		~BuildableConstructPanel(void);

		bool onBuildButtonPressed(const CEGUI::EventArgs &e);

		float getHeight()
		{
			return 130;
		}

	private:



	};
}
