#include <CEGUI.h>
#include <ac/es.h>

#include <HubInfoPanel.h>

#pragma once
namespace np
{
	class NodeInfoPanel
	{
	public:
	
		CEGUI::Window* sheet;

		CEGUI::Window* energyText;
		CEGUI::Window* temperatureText;

		np::HubInfoPanel* hubInfo;
		CEGUI::WindowManager* wmgr;

		ac::es::EntityPtr currentNode;

		void setNode( ac::es::EntityPtr node);

		void update();

		void setPosition(CEGUI::UVector2 positionVector)
		{
			sheet->setPosition(positionVector);
		}
	
		NodeInfoPanel(CEGUI::WindowManager* wmgr);
		~NodeInfoPanel(void);

	private:

	};
}

