#include <ac\es.h>
#include <vector>


/**
	ConstructComponent
	
**/

#pragma once
namespace np
{

	class Construct;

	class ConstructComponent : public ac::es::Component
	{
		AC_ES_COMPONENT(ConstructComponent)
	public:

		ac::es::EntityPtr parent;

		np::Construct* construct;

		void setConstruct( np::Construct* construct);

		ConstructComponent(np::Construct* construct = NULL, ac::es::EntityPtr parent = NULL);
		~ConstructComponent(void);


	};
}