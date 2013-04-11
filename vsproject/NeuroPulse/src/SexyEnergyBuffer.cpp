#include "SexyEnergyBuffer.h"

#include <algorithm>

np::SexyEnergyBuffer::SexyEnergyBuffer() :
	Construct( Ogre::ColourValue( 0.2, 0.6, 1.0))
{
	isReleasing = true;
	storage = 0.0;

	sexyEnergy = np::ResourceManager::getSingletonPtr()->getType( "SexyEnergy");

	inputRequirements.push_back( np::ResourceRequirement( sexyEnergy));
	outputRequirements.push_back( np::ResourceRequirement( sexyEnergy));
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
	return "Stores sexy energy so you can have some for later.";
}

void np::SexyEnergyBuffer::processInstructions( np::ResourcePacket* packet)
{
	//pimpididmpim
}
