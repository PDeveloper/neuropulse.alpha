#include <vector>

#pragma once
namespace np
{

	class ConstructInput;
	class ResourceType;
	class ResourcePacket;

	class ConstructOutput
	{
	public:

		np::ConstructInput* input;

		np::ResourceType* resourceType;

		std::vector<np::ResourcePacket*> buffer;

		ConstructOutput(void);
		~ConstructOutput(void);
	};
}