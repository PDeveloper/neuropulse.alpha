#include <string>


#pragma once
namespace np
{
	class ResourceType
	{
		virtual std::string name() = 0;
		virtual std::string description() = 0;
		virtual int id() = 0;

		bool operator==(ResourceType& other)
		{
			return id() == other.id();
		}
	};
}