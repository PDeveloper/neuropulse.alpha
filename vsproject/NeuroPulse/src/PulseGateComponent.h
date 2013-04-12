#include <ac/es.h>

#pragma once
namespace np
{

	class PulseGateComponent : public ac::es::Component
	{
		AC_ES_COMPONENT(PulseGateComponent)
	public:
		double position;
		int connectionIndex;
		ac::es::EntityPtr nodeEntity;

		PulseGateComponent( int connectionIndex, double position, ac::es::EntityPtr nodeEntity);
		~PulseGateComponent(void);
	};

}