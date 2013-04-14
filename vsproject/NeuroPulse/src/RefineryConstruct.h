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

	class RefineryConstruct : public Construct
	{
	public:

		void process();
		void processInstructions(np::ResourcePacket* packet);

		np::Construct* getUpgrade();

		std::string getName();
		std::string getDescription();

		double takeEnergy;
		double conversionRate;

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
