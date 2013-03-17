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

		int id()
		{
			return _id;
		}

		ResourceType( std::string name, std::string description, int id)
		{
			_name = name;
			_description = description;

			_id = id;
		}

		bool operator==(ResourceType& other)
		{
			return _name == other.name();
		}
	private:
		int _id;

		std::string _name;
		std::string _description;
	};
}