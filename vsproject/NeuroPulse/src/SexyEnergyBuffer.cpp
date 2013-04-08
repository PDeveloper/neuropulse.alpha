#include "SexyEnergyBuffer.h"

#include <algorithm>

np::SexyEnergyBuffer::SexyEnergyBuffer()
{
	isReleasing = true;
	storage = 0.0;

	sexyEnergy = np::ResourceManager::getSingletonPtr()->getType( "SexyEnergy");

	inputRequirements.push_back( np::ResourceRequirement( sexyEnergy));
	outputRequirements.push_back( np::ResourceRequirement( sexyEnergy));
}

void np::SexyEnergyBuffer::process()
{
	np::ResourcePacket* sexyPacket;

	storage *= 0.995;

	while ( ( sexyPacket = getNextPacket( inputRequirements.at(0))) != NULL)
	{
		storage += sexyPacket->amount;
	}

	if ( isReleasing)
	{
		ResourcePacket* product =  new ResourcePacket( sexyEnergy, std::min( 5.0, storage));

		if ( !putPacket( 0, product))
		{
			storage += product->amount;
		}
	}
}

std::string np::SexyEnergyBuffer::getName()
{
	return "Energy Storage";
}

std::string np::SexyEnergyBuffer::getDescription()
{
	return "Stores sexy energy so you can have some for later.";
}

void np::SexyEnergyBuffer::processInstructions( np::ResourcePacket* packet)
{
	//pimpididmpim
}
