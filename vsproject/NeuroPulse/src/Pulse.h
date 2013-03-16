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

		void addPacket( np::ResourcePacket* packet)
		{
			packets.push_back( packet);
		}

		np::ResourcePacket* findFirstPacket( np::ResourceType* resourceType)
		{
			for (std::list<np::ResourcePacket*>::iterator it = packets.begin(); it != packets.end(); it++)
				if ( (*it)->resourceType == resourceType)
				{
					return (*it);
				}
		}

		np::ResourcePacket* getResource( np::ResourceType* resourceType, double amount)
		{
			double value = 0.0;

			for (std::list<np::ResourcePacket*>::iterator it = packets.begin(); it != packets.end(); it++)
			{
				np::ResourcePacket* cp = (*it);
				if ( cp->resourceType == resourceType)
				{
					if ( cp->amount > amount)
					{
						cp->amount -= amount;
						value += amount;
						break;
					}
					else
					{
						value += cp->amount;
						amount -= cp->amount;

						packets.remove( cp);

						delete cp;
					}
				}
			}

			np::ResourcePacket* packet = new np::ResourcePacket( resourceType, value);

			return packet;
		}

		np::ResourcePacket* getAllResource( np::ResourceType* resourceType)
		{
			double value = 0.0;

			for (std::list<np::ResourcePacket*>::iterator it = packets.begin(); it != packets.end(); it++)
			{
				np::ResourcePacket* cp = (*it);
				if ( cp->resourceType == resourceType)
				{
					value += cp->amount;

					packets.remove( cp);

					delete cp;
				}
			}

			np::ResourcePacket* packet = new np::ResourcePacket( resourceType, value);

			return packet;
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