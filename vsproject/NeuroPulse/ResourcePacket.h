#include "ResourceType.h"


#pragma once
namespace np
{
	class ResourcePacket
	{
	public:
		ResourceType* resourceType;
		double amount;

		ResourcePacket(ResourceType* resourceType, double amount)
		{
			this->resourceType = resourceType;
			this->amount = amount;
		}
		
	};
}