#include "SexyEnergyBuffer.h"

#include <algorithm>
#include <BoolProperty.h>
#include <ListProperty.h>
#include "OutputDoubleProperty.h"
#include <hash_map>

np::SexyEnergyBuffer::SexyEnergyBuffer() :
	Construct( Ogre::ColourValue( 0.2, 0.6, 1.0))
{
	isReleasing = true;
	storage = 0.0;

	sexyEnergy = np::ResourceManager::getSingletonPtr()->getType( "Power");

	inputRequirements.push_back( np::ResourceRequirement( sexyEnergy));
	outputRequirements.push_back( np::ResourceRequirement( sexyEnergy));

	componentInterface = new np::ComponentInterface();

	componentInterface->addProperty(new OutputDoubleProperty("Energy", &storage));

	componentInterface->addProperty(new BoolProperty("Release", &isReleasing));

	/*
	std::hash_map<std::string, int>* testMap = new std::hash_map<std::string, int>();
	(*testMap)["banana"] = 0;
	(*testMap)["manana"] = 1;
	selectedItem = 0;

	componentInterface->addProperty(new ListProperty("Tasty options", &selectedItem, testMap));
	*/


}

void np::SexyEnergyBuffer::process()
{
	np::ResourcePacket* sexyPacket = getPacketOf( sexyEnergy, 40.0 - storage);

	storage += sexyPacket->amount;

	if ( isReleasing)
	{
		ResourcePacket* product =  new ResourcePacket( sexyEnergy, std::min( 0.2, storage));

		storage -= product->amount;

		if ( putPacket( 0, product) == PARTIAL)
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
	return "Stores sexy energy so you\ncan have some for later.";
}

void np::SexyEnergyBuffer::processInstructions( np::ResourcePacket* packet)
{
	//pimpididmpim
}
