#include "ConstructOutput.h"
#include "ConstructInput.h"


np::ConstructOutput::ConstructOutput(np::ResourceType* resourceType)
{
	this->resourceType = resourceType;
}


np::ConstructOutput::~ConstructOutput()
{
}

void np::ConstructOutput::connect( np::ConstructInput* target )
{
	if(this->resourceType == target->resourceType)
	{
		this->target = target;
		this->isConnected = true;

		target->target = this;
		target->isConnected = true;
	}
}

void np::ConstructOutput::disconnect()
{
	target->isConnected = false;
	this->isConnected = false;
}
