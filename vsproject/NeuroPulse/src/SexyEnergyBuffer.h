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

	class SexyEnergyBuffer : public Construct
	{
	public:

		bool isReleasing;

		void process(); 
		void processInstructions(np::ResourcePacket* packet);

		std::string getName();
		std::string getDescription();

		double takeEnergy;
		double conversionRate;
		double storage;

		int selectedItem;

		SexyEnergyBuffer();
	private:
		np::ResourceType* rawEnergy;
		np::ResourceType* sexyEnergy;
	};
}
