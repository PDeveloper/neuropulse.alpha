#include <ac/es.h>

#pragma once
namespace np
{

	class ResourceOutputComponent : public ac::es::Component
	{
		AC_ES_COMPONENT( ResourceOutputComponent)
	public:
		ac::es::EntityPtr target;
		ac::es::EntityPtr connection;
		ac::es::EntityPtr parent;

		ac::es::EntityPtr hub;

		bool connect( ac::es::EntityPtr target);
		void disconnect();

		ResourceOutputComponent(void);
		~ResourceOutputComponent(void);
	};

}