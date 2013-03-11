#include <string>


#pragma once
namespace np
{
	class ResourceType
	{
		virtual std::string name();
		virtual std::string description();
		virtual int id();

		bool operator==(ResourceType& other)
		{
			return id() == other.id();
		}
	};
}