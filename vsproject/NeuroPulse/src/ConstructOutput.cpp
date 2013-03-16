#include "ConstructOutput.h"
#include "ConstructInput.h"


np::ConstructOutput::ConstructOutput(np::ResourceType* resourceType, double maxBufferSize)
{
	this->resourceType = resourceType;
	this->maxBufferSize = maxBufferSize;

	didOverflow = false;
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

void np::ConstructOutput::putBuffer(np::ResourcePacket* packet)
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

double np::ConstructOutput::getBufferFreeSpace()
{
	double sum=0;

	std::list<np::ResourcePacket*>::iterator i;

	for(i = buffer.begin(); i != buffer.end(); ++i)
	{
		sum+=(*i)->size();
	}

	return maxBufferSize - sum;
}

void np::ConstructOutput::send()
{
	if(isConnected)
	{
		std::list<np::ResourcePacket*>::iterator i;

		while(i != buffer.end() && (*i)->size() <= target->getBufferFreeSpace())
		{
			target->putBuffer((*i));

			i = buffer.erase(i);
		}
	}

	
}
