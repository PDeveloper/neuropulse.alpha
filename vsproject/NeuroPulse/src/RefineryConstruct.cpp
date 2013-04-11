#include "RefineryConstruct.h"
#include "OgreStringConverter.h"
#include "AdvancedOgreFramework.hpp"

#include <algorithm>

np::RefineryConstruct::RefineryConstruct() :
	Construct( Ogre::ColourValue( 0.0, 0.0, 1.0))
{
	conversionRate = 0.7;

	rawEnergy = np::ResourceManager::getSingletonPtr()->getType( "RawEnergy");
	sexyEnergy = np::ResourceManager::getSingletonPtr()->getType( "SexyEnergy");

	inputRequirements.push_back( np::ResourceRequirement( rawEnergy));
	outputRequirements.push_back( np::ResourceRequirement( sexyEnergy));
}

void np::RefineryConstruct::process()
{
	double processingAmount = std::min( 0.25, getOutputLeft(0) / conversionRate);

	double totalEnergy = 0;

	np::ResourcePacket* rawPacket = getPacketOf( rawEnergy, processingAmount);

	OgreFramework::getSingletonPtr()->m_pLog->logMessage( "Refinery PROCESSING: " + Ogre::StringConverter::toString( (float)rawPacket->amount));

	ResourcePacket* product = new ResourcePacket( sexyEnergy, rawPacket->amount * conversionRate);

	putPacket( 0, product);
}

std::string np::RefineryConstruct::getName()
{
	return "Energy Refinery";
}

std::string np::RefineryConstruct::getDescription()
{
	return "Takes a percentage of raw energy from pulse and converts it to refined energy, to be used in your dick";
}

void np::RefineryConstruct::processInstructions( np::ResourcePacket* packet)
{
	//pimpididmpim
}
