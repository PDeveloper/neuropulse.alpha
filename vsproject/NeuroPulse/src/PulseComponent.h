#include <ac\es.h>

/**
	PulseComponent
	This component contains pulse info. For now, just energy.
**/

#pragma once
namespace np
{
	class PulseComponent :
		public ac::es::Component
	{
		AC_ES_COMPONENT(PulseComponent)
	public:

		double energy;

		PulseComponent( double energy);
		~PulseComponent(void);

		double get( double requestedEnergy);
		double getPercent( double rate);

	};
}