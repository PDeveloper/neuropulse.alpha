#include <ac\es.h>
#include <vector>


/**
	ConstructComponent
	
**/

#pragma once
namespace np
{

	class HubComponent;
	class Construct;

	class ConstructComponent : public ac::es::Component
	{
		AC_ES_COMPONENT(ConstructComponent)
	public:

		np::HubComponent* hubComponent;

		np::Construct* constructProcessing;

		ConstructComponent(np::Construct* constructProcessing);
		~ConstructComponent(void);


	};
}