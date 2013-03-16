#include <list>
#include "ResourcePacket.h"

#pragma once
namespace np
{

	class ConstructOutput;
	class ResourceType;
	

	class ConstructInput
	{
	public:

		np::ConstructOutput* target;

		np::ResourceType* resourceType;

		std::list<np::ResourcePacket*> buffer;
		double maxBufferSize;
		bool didOverflow;

		bool isConnected;

		ConstructInput(np::ResourceType* resourceType, double maxBufferSize);
		~ConstructInput();

		void connect(np::ConstructOutput* target);
		void disconnect();

		void putBuffer(np::ResourcePacket* packet);

		double getBufferFreeSpace();
		
	};

}