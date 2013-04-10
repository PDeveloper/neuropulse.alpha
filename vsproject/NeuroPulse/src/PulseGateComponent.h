#include <ac/es.h>

#pragma once
namespace np
{

	class PulseGateComponent : public ac::es::Component
	{
		AC_ES_COMPONENT(PulseGateComponent)
	public:
		double position;
		int connection;
		ac::es::EntityPtr nodeEntity;

		PulseGateComponent( int connection, double position, ac::es::EntityPtr nodeEntity);
		~PulseGateComponent(void);
	};

}