#include "EnergyRefinerConstruct.h"
#include "ConstructOutput.h"

np::EnergyRefineryConstruct::EnergyRefineryConstruct()
{
	conversionRate = 0.5;

	//Define inputs

	inputs.push_back(new ConstructInput(new ResourceType("RawEnergy", ""), 50));

	//Define outputs

	outputs.push_back(new ConstructOutput(new ResourceType("SexyEnergy", ""), 50));

	//outputs.push_back(new np::ConstructOutput(new ResourceType(), 100));

}



void np::EnergyRefineryConstruct::process()
{
	ConstructInput* energyInput = inputs.at(0);
	double totalEnergy = 0;

	
	std::list<np::ResourcePacket*>::iterator i;

	for(i = energyInput->buffer.begin(); i != energyInput->buffer.end(); ++i)
	{
		processInstructions(*i);

		totalEnergy += (*i)->amount;

		i = energyInput->buffer.erase(i);
	}
	

	ResourcePacket* product =  new ResourcePacket(new ResourceType("SexyEnergy", ""), totalEnergy*conversionRate, NULL);

	outputs.at(0)->putBuffer(product);

}

std::string np::EnergyRefineryConstruct::getName()
{
	return "Energy Refinery";
}

std::string np::EnergyRefineryConstruct::getDescription()
{
	return "Takes a percentage of raw energy from pulse and converts it to refined energy, to be used in your dick";
}

void np::EnergyRefineryConstruct::processInstructions( np::ResourcePacket* packet )
{
	//pimpididmpim
}
