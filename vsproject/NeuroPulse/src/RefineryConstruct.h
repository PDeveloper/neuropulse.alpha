#include <vector>
#include <string>
#include "Construct.h"
#include "Pulse.h"
#include "ResourcePacket.h"

#pragma once
namespace np
{

	class RefineryConstruct : public Construct
	{
	public:

		void process(float timeSinceLastUpdate);
		void processInstructions(np::ResourcePacket* packet);

		np::Construct* getUpgrade();

		std::string getName();
		std::string getDescription();

		double takeEnergy;
		double conversionRate;

		bool isOn;

		RefineryConstruct();

		np::Construct* getNewInstance()
		{
			return new np::RefineryConstruct();
		}

	private:
		np::ResourceType* rawEnergy;
		np::ResourceType* sexyEnergy;
	};
}
