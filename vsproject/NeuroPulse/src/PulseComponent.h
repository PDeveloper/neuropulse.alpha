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

		np::ConnectionComponent* connection;

		PulseComponent( double energy, np::ConnectionComponent* connection)
		{
			this->energy = energy;
			this->connection = connection;
		}

		~PulseComponent(void)
		{
		}

		double get( double requestedEnergy)
		{
			if ( requestedEnergy < energy)
			{
				energy -= requestedEnergy;
				return requestedEnergy;
			}
			else
			{
				energy = 0.0;
				// Must notify shit that this pulse was just destroyed.
				return energy;
			}
		}

		double getPercent( double rate)
		{
			double n_energy = energy * rate;
			energy -= n_energy;

			return n_energy;
		}
	};
}