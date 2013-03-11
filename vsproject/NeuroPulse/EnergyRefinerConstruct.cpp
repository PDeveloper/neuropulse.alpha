#include "EnergyRefinerConstruct.h"
#include "PulseFeed.h"
#include "ConstructOutput.h"

np::EnergyRefineryConstruct::EnergyRefineryConstruct()
{
	takePercentage = 0.25;
	conversionRate = 0.5;

	//Define pulseFeeds
	pulseFeeds.push_back(new np::PulseFeed(this));

	//Define inputs



	//Define outputs
	outputs.push_back(new np::ConstructOutput(new ResourceType()));
}

void np::EnergyRefineryConstruct::processIncoming( np::Pulse* pulse )
{
	//Do nothing, because fuck the system
}

void np::EnergyRefineryConstruct::processOutgoing( np::Pulse* pulse )
{
	double takenEnergy = pulse->energy * takePercentage;

	pulse->energy -= takenEnergy;

	outputs.at(0)->buffer.push_back(new ResourcePacket(new ResourceType, takenEnergy));
}

std::string np::EnergyRefineryConstruct::getName()
{
	return "Energy Refinery";
}

std::string np::EnergyRefineryConstruct::getDescription()
{
	return "Takes a percentage of raw energy from pulse and converts it to refined energy, to be used in your dick";
}
