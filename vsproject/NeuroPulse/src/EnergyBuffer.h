#include <vector>
#include <string>
#include "Construct.h"
#include "Pulse.h"
#include "ResourcePacket.h"

#pragma once
namespace np
{

	class EnergyBuffer : public Construct
	{
	public:

		bool isReleasing;

		void process(float timeSinceLastUpdate);
		void processInstructions(np::ResourcePacket* packet);

		np::Construct* getUpgrade();

		std::string getName();
		std::string getDescription();

		double takeEnergy;
		double conversionRate;
		double storage;

		bool isOn;

		EnergyBuffer();

		np::Construct* getNewInstance()
		{
			return new np::EnergyBuffer();
		}

	private:
		np::ResourceType* rawEnergy;
		np::ResourceType* sexyEnergy;
	};
}
