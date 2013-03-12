#include <vector>
#include <string>
#include "Construct.h"
#include "Pulse.h"
#include "ResourcePacket.h"

#pragma once
namespace np
{

	class PulseFeed;
	class ConstructInput;
	class ConstructOutput;

	class EnergyRefineryConstruct : public Construct
	{
	public:

		double takePercentage;
		double conversionRate;

		EnergyRefineryConstruct();

		void processIncoming(np::Pulse* pulse);
		void processOutgoing(np::Pulse* pulse);

		void update(void);

		virtual std::string getName();
		virtual std::string getDescription();
		
	};
}
