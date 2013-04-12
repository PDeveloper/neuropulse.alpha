#include <string>
#include <OgreColourValue.h>

#pragma once
namespace np
{

	class ResourceType
	{
	public:

		Ogre::ColourValue colour;

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

		double weight()
		{
			return _weight;
		}

		unsigned long int getFlag()
		{
			return flag;
		}

		ResourceType( std::string name, std::string description, Ogre::ColourValue colour, int id) :
			_name( name),
			_description( description),
			colour( colour)
		{
			_weight = 1.0;

			_id = id;
			flag = 1 << ( id + 1);
		}

		bool operator==(ResourceType& other)
		{
			return _name == other.name();
		}
	private:
		int _id;
		unsigned long int flag;
		std::string _name;
		std::string _description;

		double _weight;
	};
}