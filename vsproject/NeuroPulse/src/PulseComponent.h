#include <ac\es.h>

/**
	PulseComponent
	This component contains pulse info. For now, just energy.
**/

#pragma once
namespace np
{
	class ConnectionComponent;
	class PulseComponent :
		public ac::es::Component
	{
		AC_ES_COMPONENT(PulseComponent)
	public:

		double energy;

		np::ConnectionComponent* connection;

		PulseComponent( double energy, np::ConnectionComponent* connection);
		~PulseComponent(void);

		double get( double requestedEnergy);
		double getPercent( double rate);

	};
}