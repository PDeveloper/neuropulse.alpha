#pragma once
#include <ac/es.h>

#include <list>
#include <HubConstructionSlot.h>

namespace np
{
	class HubConstructionComponent : public ac::es::Component
	{
		AC_ES_COMPONENT(HubConstructionComponent)
	public:

		std::list<np::HubConstructionSlot> slots;

		bool hasPlayer( np::NeuroPlayer* player);
		void addPlayer( np::NeuroPlayer* player, ac::es::EntityPtr proxyHub);

		bool addToConstruction( np::NeuroPlayer* player, double amount);
		void clear(void);

		HubConstructionComponent(void);
		~HubConstructionComponent(void);
	};
}
