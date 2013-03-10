#include <ac\es.h>
#include <vector>
#include "ConstructComponent.h"


/**
	HubComponent
	Manages constructs
**/

#pragma once
namespace np
{
	class HubComponent : public ac::es::Component
	{
		AC_ES_COMPONENT(HubComponent)
	public:

		std::vector<np::ConstructComponent*> constructs;



		HubComponent();
		~HubComponent(void);


	};
}