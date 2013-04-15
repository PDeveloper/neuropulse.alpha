#include "SchematicConstruct.h"
#include <ResourceManager.h>
#include <HubComponent.h>
#include <NeuroPlayer.h>
#include <DoubleProperty.h>
#include <OutputPercentageProperty.h>


np::SchematicConstruct::SchematicConstruct(void) :
	Construct( Ogre::ColourValue( 0.28, 0.25, 0.15))
{
	sexyEnergy = np::ResourceManager::getSingletonPtr()->getType( "SexyEnergy");
	hubSchematics = np::ResourceManager::getSingletonPtr()->getType( "HubSchematic");

	inputRequirements.push_back( np::ResourceRequirement( sexyEnergy));
	outputRequirements.push_back( np::ResourceRequirement( hubSchematics));

	currentHubSchematicProgress = 0.0;

	componentInterface = new np::ComponentInterface();
	componentInterface->addProperty( new OutputPercentageProperty("Schematic", "Schematic", &currentHubSchematicProgress));
}


np::SchematicConstruct::~SchematicConstruct(void)
{
}

void np::SchematicConstruct::process(float timeSinceLastUpdate)
{
	np::ResourcePacket* sexyPacket = getPacketOf( sexyEnergy, 50.0 / 1000 * timeSinceLastUpdate );

	currentHubSchematicProgress += sexyPacket->amount * 0.02;

	if ( currentHubSchematicProgress >= 1)
	{
		currentHubSchematicProgress -= 1;

		np::NeuroPlayer* player = container->hub->getComponent<np::HubComponent>()->owner;
		np::ResourcePacket* outputPacket = new np::ResourcePacket( hubSchematics, 10.0, NULL, player->signature);

		putPacket( 0, outputPacket);
	}
}

void np::SchematicConstruct::processInstructions( np::ResourcePacket* packet )
{

}

std::string np::SchematicConstruct::getName()
{
	return "Schematics Factory";
}

std::string np::SchematicConstruct::getDescription()
{
	return "Creates hub schematics\n so you can capture moar nodes!";
}
