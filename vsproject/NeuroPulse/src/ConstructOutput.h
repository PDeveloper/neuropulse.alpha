#include <list>

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

		std::list<np::ResourcePacket*> buffer;
		double maxBufferSize;
		bool didOverflow;

		bool isConnected;

		ConstructOutput(np::ResourceType* resourceType, double maxBufferSize);
		~ConstructOutput();

		void connect(np::ConstructInput* target);
		void disconnect();

		void putBuffer(np::ResourcePacket* packet);

		double getBufferFreeSpace();

		void send();
	};
}