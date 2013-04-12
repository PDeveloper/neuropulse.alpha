#include "ResourceManager.h"
#include "Instruction.h"
#include <limits>

#pragma once
namespace np
{
	class ResourcePacket
	{
	public:
		ResourceType* resourceType;
		double amount;
		Instruction* instruction;

		unsigned long int signature;

		ResourcePacket( ResourceType* resourceType, double amount, Instruction* instruction = NULL, unsigned long int signature = std::numeric_limits<unsigned long>::max())
		{
			this->resourceType = resourceType;
			this->amount = amount;
			this->instruction = instruction;

			this->signature = signature;
		}

		double size()
		{
			//Can be used later for weights and shit
			return amount;
		}
		
	};
}