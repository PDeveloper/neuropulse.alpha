#include <CEGUI.h>
#include <ac/es.h>

#pragma once
namespace np
{
	class ConstructInfoPanel
	{
	public:
		
		CEGUI::Window* sheet;

		ac::es::EntityPtr currentNode;

		void setNode( ac::es::EntityPtr node);
		void update();
		
		ConstructInfoPanel(void);
		~ConstructInfoPanel(void);

	private:

	};
}
