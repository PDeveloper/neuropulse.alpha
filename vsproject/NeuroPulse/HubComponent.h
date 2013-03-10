#include <ac\es.h>
#include <vector>

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

		std::vector<np::ConstructComponent*> constructs;

		HubComponent();
		~HubComponent(void);

	};
}