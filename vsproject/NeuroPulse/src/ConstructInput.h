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

		np::ConstructOutput* target;

		np::ResourceType* resourceType;

		std::vector<np::ResourcePacket*> buffer;

		bool isConnected;

		ConstructInput(np::ResourceType* resourceType);
		~ConstructInput();

		void connect(np::ConstructOutput* target);
		void disconnect();
	};

}