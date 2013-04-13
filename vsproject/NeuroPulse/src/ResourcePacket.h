#include "ResourceManager.h"
#include "Instruction.h"
#include <limits>

#pragma once
#include "BitFlag.h"
namespace np
{
	class ResourcePacket
	{
	public:
		ResourceType* resourceType;
		double amount;
		Instruction* instruction;

		np::BitFlag signature;

		ResourcePacket( ResourceType* resourceType, double amount, Instruction* instruction = NULL, unsigned long int signature = std::numeric_limits<unsigned long>::max()) :
			signature( signature)
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