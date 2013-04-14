#pragma once
#include <ac/es.h>
#include <NeuroPlayer.h>
namespace np
{
	class HubConstructionSlot
	{
	public:

		np::NeuroPlayer* player;

		double amount;

		ac::es::EntityPtr proxyHub;

		HubConstructionSlot( np::NeuroPlayer* player, double amount, ac::es::EntityPtr proxyHub)
		{
			this->player	= player;
			this->amount	= amount;
			this->proxyHub	= proxyHub;
		}
	};
}
