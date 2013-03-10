#include "ResourceType.h"

#pragma once
namespace np
{
	class ConstructConnectionBase
	{
		np::ResourceType* resourceType;

		np::ConstructConnectionBase* connectedBase;

		void connect(ConstructConnectionBase* target);
		void disconnect();



	};
}