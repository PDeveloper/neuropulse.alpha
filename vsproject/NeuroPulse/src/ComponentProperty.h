#include <string>
#include <CEGUI.h>

#pragma once
namespace np
{
	class ComponentProperty
	{
	public:
		virtual std::string type() = 0;

		CEGUI::Window* sheet;
		virtual CEGUI::Window* getInitializedSheet(CEGUI::WindowManager* wmgr) = 0;

		CEGUI::WindowManager* wmgr;


		void unload()
		{
			if(sheet != NULL)
				sheet->destroy();
		}


		virtual float getHeight() = 0;

		std::string name;
	};
}