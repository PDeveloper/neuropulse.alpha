#include <list>
#include <string>
#include <algorithm>

#include <ResourcePacket.h>
#include <ResourceType.h>

#pragma once
namespace np
{
	class Pulse
	{
	public:

		double energy;

		std::list<np::ResourcePacket*> packets;

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