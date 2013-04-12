#include <CEGUI.h>
#include <ac/es.h>

#pragma once
namespace np
{
	class BufferInfoPanel
	{
	public:

		CEGUI::Window* sheet;
		CEGUI::WindowManager* wmgr;

		CEGUI::Window* resourceText;

		ac::es::EntityPtr currentBuffer;

		void setBuffer( ac::es::EntityPtr buffer);
		void update();

		void setPosition(CEGUI::UVector2 positionVector)
		{
			sheet->setPosition(positionVector);
		}

		BufferInfoPanel(CEGUI::WindowManager* wmgr);
		~BufferInfoPanel(void);

	private:

	};
}
