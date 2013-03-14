#include <ac\es.h>
#include <vector>
#include <NeuroPlayer.h>

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
		std::vector<np::ConstructComponent*> constructs;

		Ogre::BillboardSet* constructDisplay;

		double health;

		HubComponent( np::NeuroPlayer* owner);
		~HubComponent(void);

	};
}