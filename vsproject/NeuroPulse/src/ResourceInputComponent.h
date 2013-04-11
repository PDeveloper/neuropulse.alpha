#include <ac/es.h>

#pragma once
namespace np
{

	class ResourceInputComponent : public ac::es::Component
	{
		AC_ES_COMPONENT(ResourceInputComponent)
	public:
		ac::es::EntityPtr target;
		ac::es::EntityPtr parent;

		bool connect( ac::es::EntityPtr target);

		ResourceInputComponent(void);
		~ResourceInputComponent(void);
	};

}