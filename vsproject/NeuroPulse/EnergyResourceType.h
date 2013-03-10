#include <string>
#include "ResourceType.h"

#pragma once
namespace np
{
	class EnergyResourceType : public np::ResourceType
	{
		std::string name()
		{
			return "Energy";
		}

		std::string description()
		{
			return "Processed energy, use to power your dick";
		}

		int id()
		{
			return 0;
		}
	};
}