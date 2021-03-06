#include <vector>
#include <string>
#include "Construct.h"
#include "Pulse.h"
#include "ResourcePacket.h"

#pragma once
namespace np
{

	class SexyEnergyBuffer : public Construct
	{
	public:

		bool isReleasing;

		void process(float timeSinceLastUpdate); 
		void processInstructions(np::ResourcePacket* packet);

		np::Construct* getUpgrade()
		{
			return NULL;
		}

		std::string getName();
		std::string getDescription();

		double takeEnergy;
		double conversionRate;
		double storage;

		int selectedItem;

		SexyEnergyBuffer();

		np::Construct* getNewInstance()
		{
			return new np::SexyEnergyBuffer();
		}
	private:
		np::ResourceType* rawEnergy;
		np::ResourceType* sexyEnergy;
	};
}
