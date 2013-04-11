#include <CEGUI.h>
#include <ac/es.h>

#include <ComponentInterface.h>

#pragma once
namespace np
{
	class PropertyPanel
	{
	public:

		CEGUI::Window* sheet;
		
		CEGUI::WindowManager* wmgr;

		np::ComponentInterface* currentInterface;

		void setInterface(np::ComponentInterface* currentInterface);

		void update();

		void setPosition(CEGUI::UVector2 positionVector)
		{
			sheet->setPosition(positionVector);
		}

		PropertyPanel(CEGUI::WindowManager* wmgr);
		~PropertyPanel(void);

	private:

	};
}

