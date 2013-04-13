#include "RefineryConstructionConstruct.h"
#include "RefineryConstruct.h"
#include "OgreStringConverter.h"
#include "AdvancedOgreFramework.hpp"

#include <algorithm>
#include <DoubleProperty.h>

np::RefineryConstructionConstruct::RefineryConstructionConstruct() :
	Construct( Ogre::ColourValue( 0.0, 0.0, 1.0))
{
	isOn = true;

	constructionCompleted = false;
	constructionProgress = 0;

	rawEnergy = np::ResourceManager::getSingletonPtr()->getType( "RawEnergy");
	sexyEnergy = np::ResourceManager::getSingletonPtr()->getType( "SexyEnergy");

	inputRequirements.push_back( np::ResourceRequirement( rawEnergy));
	
	conversionRate = 0.01;
	takeEnergy = 50;

	componentInterface = new np::ComponentInterface();
	componentInterface->addProperty(new DoubleProperty("Build Progress", &constructionProgress, 0, 1, 0.01));
}

void np::RefineryConstructionConstruct::process()
{
	
	np::ResourcePacket* rawPacket = getPacketOf( rawEnergy, takeEnergy);
	

	//OgreFramework::getSingletonPtr()->m_pLog->logMessage( "Refinery PROCESSING: " + Ogre::StringConverter::toString( (float)rawPacket->amount));

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
	return "Takes a percentage of raw energy from pulse and converts it to refined energy, to be used in your dick";
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
