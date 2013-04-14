#include <string>
#include <ComponentProperty.h>
#include <AdvancedOgreFramework.hpp>

#pragma once
namespace np
{
	class BoolProperty : public ComponentProperty
	{
	public:
		BoolProperty(std::string name, bool* value)
		{
			sheet = NULL;

			this->name = name;
			this->value = value;			
		}

		std::string type()
		{
			return "Bool";
		}

		CEGUI::Window* getInitializedSheet(CEGUI::WindowManager* wmgr)
		{
			this->wmgr = wmgr;



			CEGUI::Checkbox* checkbox = static_cast<CEGUI::Checkbox*>(wmgr->createWindow("TaharezLook/Checkbox", name));

			sheet = checkbox;

			checkbox->setText(name);
			checkbox->subscribeEvent(CEGUI::Checkbox::EventCheckStateChanged, CEGUI::Event::Subscriber(&BoolProperty::onCheckedStateChanged, this));
			checkbox->setSelected(*value);
			checkbox->setFont("Text");
			

			return sheet;
		}


		bool* value;
		

		bool isEnabled;

		bool onCheckedStateChanged(const CEGUI::EventArgs &e)
		{
			OgreFramework::getSingletonPtr()->m_pLog->logMessage("Bing "+Ogre::StringConverter::toString(*value));

			*value = (static_cast<CEGUI::Checkbox*>(sheet))->isSelected();

			OgreFramework::getSingletonPtr()->m_pLog->logMessage("Bong "+Ogre::StringConverter::toString(*value));

			return true;
		}

		float getHeight()
		{
			return 20;
		}

		void update()
		{
			
		}
	};
}