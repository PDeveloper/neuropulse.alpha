#pragma once
namespace np
{
	class Pulse
	{
	public:

		double energy;

		Pulse( double energy)
		{
			this->energy = energy;
		}

		~Pulse(void)
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
				double ne = energy;
				energy = 0.0;
				// Must notify shit that this pulse was just destroyed.
				return ne;
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