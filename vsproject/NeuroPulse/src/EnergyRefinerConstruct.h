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

		double takeEnergy;
		double conversionRate;

		EnergyRefineryConstruct();

		void process();
		void processInstructions(np::ResourcePacket* packet);

		std::string getName();
		std::string getDescription();
		
	};
}
