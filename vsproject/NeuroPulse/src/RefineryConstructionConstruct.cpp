#include "RefineryConstructionConstruct.h"
#include "RefineryConstruct.h"
#include "OgreStringConverter.h"
#include "AdvancedOgreFramework.hpp"

#include <algorithm>
#include <DoubleProperty.h>
#include <OutputPercentageProperty.h>

np::RefineryConstructionConstruct::RefineryConstructionConstruct() :
	Construct( Ogre::ColourValue( 0.0, 0.0, 1.0))
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

void np::RefineryConstructionConstruct::process(float timeSinceLastUpdate)
{
	
	double processingAmount = 10.0 / 1000 * timeSinceLastUpdate;

	np::ResourcePacket* rawPacket = getPacketOf( rawEnergy, processingAmount);
	

	//OgreFramework::getSingletonPtr()->m_pLog->logMessage( "Refinery BUILDING: " + Ogre::StringConverter::toString( (float)rawPacket->amount));

	constructionProgress += rawPacket->amount * conversionRate;

	if(constructionProgress >= 1)
		constructionCompleted = true;
}

std::string np::RefineryConstructionConstruct::getName()
{
	return "Energy Refinery";
}

std::string np::RefineryConstructionConstruct::getDescription()
{
	return "Takes a percentage of energy\nfrom pulse and converts it to power.";
}

void np::RefineryConstructionConstruct::processInstructions( np::ResourcePacket* packet)
{
	//pimpididmpim
}

np::Construct* np::RefineryConstructionConstruct::getUpgrade()
{
	if(constructionCompleted)
	{
		return new RefineryConstruct();
	}
	else
	{
		return NULL;
	}
}
