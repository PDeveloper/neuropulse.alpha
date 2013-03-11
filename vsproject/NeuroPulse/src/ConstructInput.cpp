#include "ConstructInput.h"
#include "ConstructOutput.h"

np::ConstructInput::ConstructInput(np::ResourceType* resourceType)
{
	this->resourceType = resourceType;
}

np::ConstructInput::~ConstructInput()
{
}

void np::ConstructInput::connect(np::ConstructOutput* target)
{
	if(this->resourceType == target->resourceType)
	{
		this->target = target;
		this->isConnected = true;

		target->target = this;
		target->isConnected = true;
	}
}

void np::ConstructInput::disconnect()
{
	target->isConnected = false;
	this->isConnected = false;
}
