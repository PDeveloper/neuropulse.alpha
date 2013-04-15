#include <vector>
#include <string>
#include "Construct.h"
#include "Pulse.h"
#include "ResourcePacket.h"

#pragma once
namespace np
{

	class SexyEnergyBufferConstruction : public Construct
	{
	public:

		void process(float timeSinceLastUpdate);
		void processInstructions(np::ResourcePacket* packet);

		np::Construct* getUpgrade();

		std::string getName();
		std::string getDescription();

		double takeEnergy;
		double conversionRate;

		SexyEnergyBufferConstruction();

		np::Construct* getNewInstance()
		{
			return new np::SexyEnergyBufferConstruction();
		}
	private:
		np::ResourceType* rawEnergy;
		np::ResourceType* sexyEnergy;

		bool constructionCompleted;
		double constructionProgress;

	};
}
