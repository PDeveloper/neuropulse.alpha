#include <ac\es.h>
#include <vector>
#include "HubComponent.h"


/**
	ConstructComponent
	
**/

#pragma once
namespace np
{
	class ConstructComponent : public ac::es::Component
	{
		AC_ES_COMPONENT(ConstructComponent)
	public:

		np::HubComponent* hubComponent;

		np::ConstructProcessing* constructProcessing;

		ConstructComponent(np::ConstructProcessing* constructProcessing);
		~ConstructComponent(void);


	};
}