#include <string>

#pragma once
namespace np
{

	class ResourceType
	{
	public:

		std::string name()
		{
			return _name;
		}

		std::string description()
		{
			return _description;
		}

		ResourceType( std::string name, std::string description)
		{
			_name = name;
			_description = description;
		}

		bool operator==(ResourceType& other)
		{
			return _name == other.name();
		}
	private:
		std::string _name;
		std::string _description;
	};
}