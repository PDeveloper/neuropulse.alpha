#include <ac\es.h>
#include <TransformComponent.h>


/**
	ConstructConnectionComponent
	For drawing connections between constructs
**/

#pragma once
namespace np
{
	class ConstructConnectionComponent : public ac::es::Component
	{
		AC_ES_COMPONENT(ConstructConnectionComponent)
	public:

		np::TransformComponent* target1;
		np::TransformComponent* target2;

		ConstructConnectionComponent( np::TransformComponent* target1, np::TransformComponent* target2);
		~ConstructConnectionComponent(void);


	};
}