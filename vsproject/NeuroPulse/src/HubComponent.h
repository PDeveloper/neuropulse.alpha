#include <ac\es.h>
#include <vector>

#include <NeuroPlayer.h>
#include <OgreEntity.h>

/**
	HubComponent
	Manages constructs
**/

#pragma once
namespace np
{

	class ConstructComponent;

	class HubComponent : public ac::es::Component
	{
		AC_ES_COMPONENT(HubComponent)
	public:

		np::NeuroPlayer* owner;
		std::vector<ac::es::EntityPtr> constructs;

		Ogre::Entity* display;

		//Heat stuff
		double health;
		
		double overheatTemperature;
		double overheatDamage;
		

		HubComponent( np::NeuroPlayer* owner);
		~HubComponent(void);

		void destroy();

	};
}