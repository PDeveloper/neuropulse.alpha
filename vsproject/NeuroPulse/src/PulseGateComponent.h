#include <ac/es.h>

#pragma once
namespace np
{

	class PulseGateComponent : public ac::es::Component
	{
		AC_ES_COMPONENT(PulseGateComponent)
	public:
		PulseGateComponent(void);
		~PulseGateComponent(void);
	};

}