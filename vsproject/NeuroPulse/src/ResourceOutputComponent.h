#include <ac/es.h>

#pragma once
namespace np
{

	class ResourceOutputComponent : public ac::es::Component
	{
		AC_ES_COMPONENT( ResourceOutputComponent)
	public:
		ac::es::EntityPtr target;

		bool connect( ac::es::EntityPtr target);

		ResourceOutputComponent(void);
		~ResourceOutputComponent(void);
	};

}