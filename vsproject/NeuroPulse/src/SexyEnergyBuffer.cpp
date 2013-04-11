#include "SexyEnergyBuffer.h"

#include <algorithm>
#include <BoolProperty.h>
#include <ListProperty.h>
#include <hash_map>

np::SexyEnergyBuffer::SexyEnergyBuffer()
{
	isOn = true;

	isReleasing = true;
	storage = 0.0;

	sexyEnergy = np::ResourceManager::getSingletonPtr()->getType( "SexyEnergy");

	inputRequirements.push_back( np::ResourceRequirement( sexyEnergy));
	outputRequirements.push_back( np::ResourceRequirement( sexyEnergy));

	componentInterface = new np::ComponentInterface();
	componentInterface->addProperty(new BoolProperty("Release", &isReleasing));

	std::hash_map<std::string, int>* testMap = new std::hash_map<std::string, int>();
	(*testMap)["banana"] = 0;
	(*testMap)["manana"] = 1;
	selectedItem = 0;

	componentInterface->addProperty(new ListProperty("Tasty options", &selectedItem, testMap));

	

	

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
