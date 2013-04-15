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
		ListProperty(std::string uniqueId, std::string name, int* value, std::hash_map<std::string, int>* valueMap)
		{
			sheet = NULL;

			this->uniqueId = uniqueId;
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
			sheet = wmgr->createWindow("DefaultWindow", uniqueId+name+"/Main");


			title = wmgr->createWindow("TaharezLook/StaticText", uniqueId+name+"/Title");
			title->setPosition( CEGUI::UVector2( CEGUI::UDim( 0.0, 0), CEGUI::UDim( 0, 0)));
			title->setSize(CEGUI::UVector2(CEGUI::UDim(0, 200), CEGUI::UDim(0, 30)));
			title->setText(name);
			title->setFont("Text");

			sheet->addChildWindow(title);



			combobox = static_cast<CEGUI::Combobox*>(wmgr->createWindow("TaharezLook/Combobox", uniqueId+name+"/Combobox"));
			combobox->subscribeEvent(CEGUI::Combobox::EventListSelectionChanged, CEGUI::Event::Subscriber(&ListProperty::onListSelectionChanged, this));
			combobox->setReadOnly(true);
			combobox->setFont("Text");

			combobox->setPosition(CEGUI::UVector2( CEGUI::UDim( 0.0, 0), CEGUI::UDim( 0, 30)));
			combobox->setSize(CEGUI::UVector2( CEGUI::UDim( 0.0, 200), CEGUI::UDim( 0, 30 + valueMap->size()*30)));


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

			
			//combobox->getDropList()->setSize(CEGUI::UVector2( CEGUI::UDim( 0.0, 200), CEGUI::UDim( 0, valueMap->size()*30)));

			CEGUI::PushButton* listButton = combobox->getPushButton();
			listButton->subscribeEvent(CEGUI::PushButton::EventMouseButtonDown, CEGUI::Event::Subscriber(&ListProperty::buttonClicked, this));

			

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

		bool buttonClicked(const CEGUI::EventArgs &e)
		{
			OgreFramework::getSingletonPtr()->m_pLog->logMessage("Bing ");

			/*
			if(combobox->isDropDownListVisible())
			{
				OgreFramework::getSingletonPtr()->m_pLog->logMessage("Bang ");
				combobox->hideDropList();
			}
			else
			{
				OgreFramework::getSingletonPtr()->m_pLog->logMessage("Bong ");
				combobox->showDropList();
			}
			*/

			combobox->showDropList();

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