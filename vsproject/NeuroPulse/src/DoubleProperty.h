#include <string>
#include <ComponentProperty.h>

#pragma once
namespace np
{
	class DoubleProperty : public ComponentProperty
	{
	public:
		DoubleProperty(std::string name, double* value, double min, double max, double step)
		{
			sheet = NULL;

			this->name = name;
			this->value = value;
			this->min = min;
			this->max = max;
			this->step = step;
		}

		std::string type()
		{
			return "Double";
		}

		CEGUI::Window* getInitializedSheet(CEGUI::WindowManager* wmgr)
		{
			this->wmgr = wmgr;
			sheet = wmgr->createWindow("DefaultWindow", name+"/Main");


			title = wmgr->createWindow("TaharezLook/StaticText", name+"/Title");
			title->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.0, 0), CEGUI::UDim( 0, 0)));
			title->setSize(CEGUI::UVector2(CEGUI::UDim(0, 200), CEGUI::UDim(0, 30)));
			title->setText(name);

			sheet->addChildWindow(title);

			spinner = static_cast<CEGUI::Spinner*>(wmgr->createWindow("TaharezLook/Spinner", name+"/Spinner"));
			spinner->setAutoRepeatDelay(5);
			spinner->setAutoRepeatRate(0.5);
			spinner->setMouseAutoRepeatEnabled(false);
			spinner->setTextInputMode(CEGUI::Spinner::FloatingPoint); // FloatingPoint, Integer, Hexadecimal, Octal
			spinner->setMinimumValue(min);
			spinner->setMaximumValue(max);
			spinner->setStepSize(step);
			spinner->setCurrentValue(*value);
			spinner->subscribeEvent(CEGUI::Spinner::EventValueChanged, CEGUI::Event::Subscriber(&DoubleProperty::onSpinnerValueChanged, this));
			
			spinner->setPosition(CEGUI::UVector2( CEGUI::UDim( 0.0, 0), CEGUI::UDim( 0, 30)));
			spinner->setSize(CEGUI::UVector2( CEGUI::UDim( 0.0, 200), CEGUI::UDim( 0, 40)));
			spinner->activate();
			
			sheet->addChildWindow(spinner);

			return sheet;
		}


		double* value;

		double min, max, step;

		bool isEnabled;

		CEGUI::Spinner* spinner;
		CEGUI::Window* title;

		bool onSpinnerValueChanged(const CEGUI::EventArgs &e)
		{
			*value = spinner->getCurrentValue();

			return true;
		}

		float getHeight()
		{
			return 70;
		}
	};
}