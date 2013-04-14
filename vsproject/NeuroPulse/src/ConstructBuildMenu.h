#include <CEGUI.h>
#include <ac/es.h>
#include <PropertyPanel.h>
#include <Construct.h>
#include <BuildableConstructPanel.h>

#pragma once
namespace np
{
	class ConstructBuildMenu
	{
	public:

		static std::vector<np::Construct*>* buildableConstructs;
		static np::GameObjectFactory* objectFactory;


		std::vector<np::BuildableConstructPanel*>* panels;

		CEGUI::Window* sheet;
		CEGUI::WindowManager* wmgr;
		
		ac::es::EntityPtr entity;

		void setEntity( ac::es::EntityPtr entity);
		void update();

		void setPosition(CEGUI::UVector2 positionVector)
		{
			sheet->setPosition(positionVector);
		}

		ConstructBuildMenu(CEGUI::WindowManager* wmgr);
		~ConstructBuildMenu(void);

	private:

	};
}
