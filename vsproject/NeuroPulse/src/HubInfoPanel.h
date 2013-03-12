#include <CEGUI.h>
#include <ac/es.h>

#pragma once
namespace np
{
	class HubInfoPanel
	{
	public:

		CEGUI::Window* sheet;

		ac::es::EntityPtr currentHub;

		void setHub( ac::es::EntityPtr hub);

		void update();

		HubInfoPanel(void);
		~HubInfoPanel(void);
	};
}

