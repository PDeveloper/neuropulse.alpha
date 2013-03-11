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

		np::ConstructInput* target;

		np::ResourceType* resourceType;

		std::vector<np::ResourcePacket*> buffer;

		bool isConnected;

		ConstructOutput(np::ResourceType* resourceType);
		~ConstructOutput();

		void connect(np::ConstructInput* target);
		void disconnect();
	};
}