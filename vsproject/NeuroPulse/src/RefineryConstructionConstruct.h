#include <vector>
#include <string>
#include "Construct.h"
#include "Pulse.h"
#include "ResourcePacket.h"

#pragma once
namespace np
{

	class RefineryConstructionConstruct : public Construct
	{
	public:

		void process(float timeSinceLastUpdate);
		void processInstructions(np::ResourcePacket* packet);

		np::Construct* getUpgrade();

		std::string getName();
		std::string getDescription();

		double takeEnergy;
		double conversionRate;

		RefineryConstructionConstruct();

		np::Construct* getNewInstance()
		{
			return new np::RefineryConstructionConstruct();
		}

	private:
		np::ResourceType* rawEnergy;
		np::ResourceType* sexyEnergy;

		bool constructionCompleted;
		double constructionProgress;

	};
}
