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
		np::HubInfoPanel* hubInfo;

		ac::es::EntityPtr currentNode;

		void setNode( ac::es::EntityPtr node);

		void update();
	
		NodeInfoPanel(void);
		~NodeInfoPanel(void);

	private:

	};
}

