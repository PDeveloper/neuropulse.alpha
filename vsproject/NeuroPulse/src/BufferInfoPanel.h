#include <CEGUI.h>
#include <ac/es.h>
#include <hash_map>
#include <ComponentInterface.h>
#include <PropertyPanel.h>

#pragma once
namespace np
{
	class BufferInfoPanel
	{
	public:

		CEGUI::Window* sheet;
		CEGUI::WindowManager* wmgr;

		CEGUI::Window* resourceText;

		np::ComponentInterface* componentInterface;
		std::hash_map<std::string, double>* amounts;

		np::PropertyPanel* propertyPanel;

		ac::es::EntityPtr currentBuffer;

		void setBuffer( ac::es::EntityPtr buffer);
		void update();

		void setPosition(CEGUI::UVector2 positionVector)
		{
			sheet->setPosition(positionVector);
		}

		BufferInfoPanel(CEGUI::WindowManager* wmgr);
		~BufferInfoPanel(void);

		float getHeight()
		{
			return sheet->getHeight().d_offset;
		}

	private:

	};
}
