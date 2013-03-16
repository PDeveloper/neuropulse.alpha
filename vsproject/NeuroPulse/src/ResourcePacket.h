#include "ResourceManager.h"
#include "Instruction.h"

#pragma once
namespace np
{
	class ResourcePacket
	{
	public:
		ResourceType* resourceType;
		double amount;
		Instruction* instruction;

		ResourcePacket( ResourceType* resourceType, double amount, Instruction* instruction = NULL)
		{
			this->resourceType = resourceType;
			this->amount = amount;
			this->instruction = instruction;
		}

		double size()
		{
			//Can be used later for weights and shit
			return amount;
		}
		
	};
}