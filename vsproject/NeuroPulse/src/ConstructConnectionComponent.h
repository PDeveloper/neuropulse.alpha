#include <ac\es.h>
#include <TransformComponent.h>
#include "ConstructInput.h"
#include "ConstructOutput.h"


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

		ac::es::EntityPtr entity1;
		ac::es::EntityPtr entity2;

		np::TransformComponent* target1;
		np::TransformComponent* target2;

		ConstructConnectionComponent( ac::es::EntityPtr entity1, ac::es::EntityPtr entity2);
		~ConstructConnectionComponent(void);


	};
}