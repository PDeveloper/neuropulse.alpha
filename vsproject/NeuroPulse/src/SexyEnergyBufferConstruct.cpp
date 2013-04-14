#include "SexyEnergyBufferConstruction.h"
#include "SexyEnergyBuffer.h"
#include "OgreStringConverter.h"
#include "AdvancedOgreFramework.hpp"

#include <algorithm>
#include <DoubleProperty.h>
#include <OutputPercentageProperty.h>

np::SexyEnergyBufferConstruction::SexyEnergyBufferConstruction() :
	Construct( Ogre::ColourValue( 0.2, 0.6, 1.0))
{
	
	constructionCompleted = false;
	constructionProgress = 0;

	rawEnergy = np::ResourceManager::getSingletonPtr()->getType( "RawEnergy");
	sexyEnergy = np::ResourceManager::getSingletonPtr()->getType( "SexyEnergy");

	inputRequirements.push_back( np::ResourceRequirement( sexyEnergy));

	conversionRate = 0.01;
	takeEnergy = 50;

	componentInterface = new np::ComponentInterface();
	componentInterface->addProperty(new OutputPercentageProperty("Build Progress", &constructionProgress));
}

void np::SexyEnergyBufferConstruction::process()
{

	np::ResourcePacket* sexyPacket = getPacketOf( sexyEnergy, takeEnergy);


	//OgreFramework::getSingletonPtr()->m_pLog->logMessage( "Refinery PROCESSING: " + Ogre::StringConverter::toString( (float)rawPacket->amount));

	constructionProgress += sexyPacket->amount * conversionRate;

	if(constructionProgress >= 1)
		constructionCompleted = true;
}

std::string np::SexyEnergyBufferConstruction::getName()
{
	return "Energy Storage";
}

std::string np::SexyEnergyBufferConstruction::getDescription()
{
	return "Stores sexy energy so you\ncan have some for later.";
}

void np::SexyEnergyBufferConstruction::processInstructions( np::ResourcePacket* packet)
{
	//pimpididmpim
}

np::Construct* np::SexyEnergyBufferConstruction::getUpgrade()
{
	if(constructionCompleted)
	{
		return new SexyEnergyBuffer();
	}
	else
	{
		return NULL;
	}
}
