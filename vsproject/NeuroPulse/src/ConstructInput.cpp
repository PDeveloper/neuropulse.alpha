#include "ConstructInput.h"
#include "ConstructOutput.h"

np::ConstructInput::ConstructInput(np::ResourceType* resourceType, double maxBufferSize)
{
	this->resourceType = resourceType;
	this->maxBufferSize = maxBufferSize;

	didOverflow = false;
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

void np::ConstructInput::putBuffer(np::ResourcePacket* packet)
{
	if(packet->size() < maxBufferSize - getBufferFreeSpace() && packet->resourceType == resourceType)
	{
		buffer.push_back(packet);
	}
	else
	{
		//What else??!?!?!?!?!?!?
	}
}

double np::ConstructInput::getBufferFreeSpace()
{
	double sum=0;

	std::list<np::ResourcePacket*>::iterator i;

	for(i = buffer.begin(); i != buffer.end(); ++i)
	{
		sum+=(*i)->size();
	}

	return maxBufferSize - sum;
}

