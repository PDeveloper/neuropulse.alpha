#include "RefineryConstruct.h"
#include "OgreStringConverter.h"
#include "AdvancedOgreFramework.hpp"

np::RefineryConstruct::RefineryConstruct()
{
	conversionRate = 0.5;

	rawEnergy = np::ResourceManager::getSingletonPtr()->getType( "RawEnergy");
	sexyEnergy = np::ResourceManager::getSingletonPtr()->getType( "SexyEnergy");

	inputRequirements.push_back( np::ResourceRequirement( rawEnergy));
	outputRequirements.push_back( np::ResourceRequirement( sexyEnergy));
}

void np::RefineryConstruct::process()
{
	double processingAmount = 50.0;

	double totalEnergy = 0;

	np::ResourcePacket* rawPacket = getPacketOf( rawEnergy, processingAmount);

	OgreFramework::getSingletonPtr()->m_pLog->logMessage( "Refinery PROCESSING: " + Ogre::StringConverter::toString( (float)rawPacket->amount));

	ResourcePacket* product = new ResourcePacket( sexyEnergy, rawPacket->amount);

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
