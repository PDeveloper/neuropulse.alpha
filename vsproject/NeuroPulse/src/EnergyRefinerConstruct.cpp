#include "EnergyRefinerConstruct.h"

np::EnergyRefineryConstruct::EnergyRefineryConstruct()
{
	conversionRate = 0.5;

	rawEnergy = np::ResourceManager::getSingletonPtr()->getType( "RawEnergy");
	sexyEnergy = np::ResourceManager::getSingletonPtr()->getType( "SexyEnergy");

	inputRequirements.push_back( np::ResourceRequirement( rawEnergy));
	outputRequirements.push_back( np::ResourceRequirement( sexyEnergy));
}

void np::EnergyRefineryConstruct::process()
{
	double totalEnergy = 0;

	np::ResourcePacket* rawPacket;

	while ( ( rawPacket = getNextPacket( inputRequirements.at(0))) != NULL)
	{
		totalEnergy += rawPacket->amount;
	}

	ResourcePacket* product =  new ResourcePacket( sexyEnergy, totalEnergy * conversionRate);

	putPacket( 0, product);

}

std::string np::EnergyRefineryConstruct::getName()
{
	return "Energy Refinery";
}

std::string np::EnergyRefineryConstruct::getDescription()
{
	return "Takes a percentage of raw energy from pulse and converts it to refined energy, to be used in your dick";
}

void np::EnergyRefineryConstruct::processInstructions( np::ResourcePacket* packet)
{
	//pimpididmpim
}
