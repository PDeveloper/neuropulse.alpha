#include <ac\es.h>
#include <vector>
#include "ConstructProcessing.h";

/**
	ConstructComponent
	
**/

#pragma once
namespace np
{

	class HubComponent;

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