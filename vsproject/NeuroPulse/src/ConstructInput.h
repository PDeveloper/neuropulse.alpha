#include <vector>

#pragma once
namespace np
{

	class ConstructOutput;
	class ResourceType;
	class ResourcePacket;

	class ConstructInput
	{
	public:

		np::ConstructOutput* output;

		np::ResourceType* resourceType;

		std::vector<np::ResourcePacket*> buffer;

		ConstructInput(void);
		~ConstructInput(void);
	};

}