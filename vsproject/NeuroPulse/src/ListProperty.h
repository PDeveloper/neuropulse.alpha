#include <string>
#include <hash_map>
#include <ComponentProperty.h>
#include <AdvancedOgreFramework.hpp>

#pragma once
namespace np
{
	class ListProperty : public ComponentProperty
	{
	public:
		ListProperty(std::string name, int* value, std::hash_map<std::string, int>* valueMap)
		{
			sheet = NULL;

			this->name = name;
			this->value = value;
			this->valueMap = valueMap;

		}

		std::string type()
		{
			return "List";
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

			combobox = static_cast<CEGUI::Combobox*>(wmgr->createWindow("TaharezLook/Combobox", name+"/Combobox"));
			combobox->subscribeEvent(CEGUI::Combobox::EventListSelectionChanged, CEGUI::Event::Subscriber(&ListProperty::onListSelectionChanged, this));
			combobox->setReadOnly(true);

			int i=0;
			for (std::hash_map<std::string, int>::iterator iter = valueMap->begin(); 
				iter != valueMap->end(); 
				++iter)
			{
				CEGUI::ListboxTextItem* item = new CEGUI::ListboxTextItem(iter->first, iter->second);
				item->setSelectionBrushImage("TaharezLook", "MultiListSelectionBrush");
				combobox->addItem(item);

				//OgreFramework::getSingletonPtr()->m_pLog->logMessage("Bing "+Ogre::StringConverter::toString(*value)+" "+Ogre::StringConverter::toString(iter->second));

				if(iter->second == *value)
				{
					//OgreFramework::getSingletonPtr()->m_pLog->logMessage("Bing bong "+iter->first);
					combobox->setItemSelectState(item, true);
				}
				//OgreFramework::getSingletonPtr()->m_pLog->logMessage("Bing bong "+iter->first);
				i++;
			}
			

			CEGUI::ListboxItem* pItem = combobox->getDropList()->getFirstSelectedItem();
			if(pItem!=NULL)
				combobox->getEditbox()->setText(pItem->getText());

			combobox->setPosition(CEGUI::UVector2( CEGUI::UDim( 0.0, 0), CEGUI::UDim( 0, 30)));
			combobox->setSize(CEGUI::UVector2( CEGUI::UDim( 0.0, 200), CEGUI::UDim( 0, 30 + valueMap->size()*30)));

			//combobox->getDropList()->setSize(CEGUI::UVector2( CEGUI::UDim( 0.0, 200), CEGUI::UDim( 0, valueMap->size()*30)));
			

			sheet->addChildWindow(combobox);

			return sheet;
		}


		int* value;

		std::hash_map<std::string, int>* valueMap;

		bool isEnabled;

		CEGUI::Combobox* combobox;
		CEGUI::Window* title;

		bool onListSelectionChanged(const CEGUI::EventArgs &e)
		{
			CEGUI::ListboxItem* listItem = combobox->getSelectedItem();
			/*
			std::string strItemText = "";

			if (listItem != NULL)
			{
				strItemText = listItem->getText().c_str();
			}



			*value = valueMap->find(strItemText)->second;
			*/

			if(listItem != NULL)
				*value = listItem->getID();

			return true;
		}

		float getHeight()
		{
			return 70 + valueMap->size()*30;
		}

		void update()
		{

		}
	};
}