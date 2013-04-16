#include "EnergyBufferConstruction.h"
#include "RefineryConstruct.h"
#include "OgreStringConverter.h"
#include "AdvancedOgreFramework.hpp"

#include <algorithm>
#include <DoubleProperty.h>
#include <OutputPercentageProperty.h>
#include <EnergyBuffer.h>

np::EnergyBufferConstruction::EnergyBufferConstruction() :
	Construct( Ogre::ColourValue( 0.8, 0.8, 0.05))
{
	constructionCompleted = false;
	constructionProgress = 0;

	rawEnergy = np::ResourceManager::getSingletonPtr()->getType( "Energy");
	sexyEnergy = np::ResourceManager::getSingletonPtr()->getType( "Power");

	inputRequirements.push_back( np::ResourceRequirement( rawEnergy));

	conversionRate = 0.01;

	componentInterface = new np::ComponentInterface();
	componentInterface->addProperty(new OutputPercentageProperty("RefineryConstruction", "Build Progress", &constructionProgress));
}

void np::EnergyBufferConstruction::process(float timeSinceLastUpdate)
{

	double processingAmount = 10.0 / 1000 * timeSinceLastUpdate;

	np::ResourcePacket* rawPacket = getPacketOf( rawEnergy, processingAmount);


	//OgreFramework::getSingletonPtr()->m_pLog->logMessage( "Refinery BUILDING: " + Ogre::StringConverter::toString( (float)rawPacket->amount));

	constructionProgress += rawPacket->amount * conversionRate;

	if(constructionProgress >= 1)
		constructionCompleted = true;
}

std::string np::EnergyBufferConstruction::getName()
{
	return "Energy Buffer";
}

std::string np::EnergyBufferConstruction::getDescription()
{
	return "Stores energy that can be released later.";
}

void np::EnergyBufferConstruction::processInstructions( np::ResourcePacket* packet)
{
	//pimpididmpim
}

np::Construct* np::EnergyBufferConstruction::getUpgrade()
{
	if(constructionCompleted)
	{
		return new EnergyBuffer();
	}
	else
	{
		return NULL;
	}
}
