#include "SchematicConstruction.h"
#include <ResourceManager.h>
#include <OutputPercentageProperty.h>
#include <SchematicConstruct.h>

np::SchematicConstruction::SchematicConstruction(void) :
	Construct( Ogre::ColourValue( 0.28, 0.25, 0.15))
{
	constructionCompleted = false;
	constructionProgress = 0;

	sexyEnergy = np::ResourceManager::getSingletonPtr()->getType( "Power");

	inputRequirements.push_back( np::ResourceRequirement( sexyEnergy));

	conversionRate = 0.008;
	takeEnergy = 50 / 1000.0;

	componentInterface = new np::ComponentInterface();
	componentInterface->addProperty(new OutputPercentageProperty("SchematicConstruction", "Build Progress", &constructionProgress));
}


np::SchematicConstruction::~SchematicConstruction(void)
{
}

void np::SchematicConstruction::process(float timeSinceLastUpdate)
{
	np::ResourcePacket* sexyPacket = getPacketOf( sexyEnergy, takeEnergy* timeSinceLastUpdate);


	//OgreFramework::getSingletonPtr()->m_pLog->logMessage( "Refinery PROCESSING: " + Ogre::StringConverter::toString( (float)rawPacket->amount));

	constructionProgress += sexyPacket->amount * conversionRate;

	if(constructionProgress >= 1)
		constructionCompleted = true;
}

void np::SchematicConstruction::processInstructions( np::ResourcePacket* packet )
{

}

np::Construct* np::SchematicConstruction::getUpgrade()
{
	if(constructionCompleted)
	{
		return new SchematicConstruct();
	}
	else
	{
		return NULL;
	}
}

std::string np::SchematicConstruction::getName()
{
	return "Schematics Factory";
}

std::string np::SchematicConstruction::getDescription()
{
	return "Creates hub schematics\nso you can capture moar nodes!";
}
