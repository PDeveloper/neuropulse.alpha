#include "EnergyBuffer.h"
#include "OgreStringConverter.h"
#include "AdvancedOgreFramework.hpp"

#include <algorithm>
#include <DoubleProperty.h>
#include <BoolProperty.h>
#include <OutputDoubleProperty.h>

np::EnergyBuffer::EnergyBuffer() :
	Construct( Ogre::ColourValue( 0.8, 0.8, 0.05))
{
	conversionRate = 0.7;

	isReleasing = false;

	isOn = true;

	rawEnergy = np::ResourceManager::getSingletonPtr()->getType( "Energy");

	inputRequirements.push_back( np::ResourceRequirement( rawEnergy));
	outputRequirements.push_back( np::ResourceRequirement( rawEnergy));

	componentInterface = new np::ComponentInterface();

	componentInterface->addProperty(new OutputDoubleProperty("Buffer", "Energy", &storage));

	componentInterface->addProperty(new BoolProperty("Buffer", "Release", &isReleasing));
}

void np::EnergyBuffer::process(float timeSinceLastUpdate)
{
	double processingAmount = std::min( 0.25, getOutputLeft(0) / (conversionRate ));

	double totalEnergy = 0;

	np::ResourcePacket* rawPacket = getPacketOf( rawEnergy, 40.0 - storage);

	storage += rawPacket->amount;

	if ( isReleasing)
	{
		ResourcePacket* product =  new ResourcePacket( rawEnergy, std::min( 40.0, storage));

		storage -= product->amount;

		if ( putPacket( 0, product) == PARTIAL)
		{
			storage += product->amount;
		}
	}
}

std::string np::EnergyBuffer::getName()
{
	return "Energy Buffer";
}

std::string np::EnergyBuffer::getDescription()
{
	return "Stores energy that can be released later.";
}

void np::EnergyBuffer::processInstructions( np::ResourcePacket* packet)
{
	//pimpididmpim
}

np::Construct* np::EnergyBuffer::getUpgrade()
{
	return NULL;
}
