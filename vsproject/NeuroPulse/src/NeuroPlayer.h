#include <string>
#include <OgreColourValue.h>

#pragma once
namespace np
{

	class NeuroPlayer
	{
	public:

		std::string name;

		Ogre::ColourValue colour;

		unsigned long int signature;

		NeuroPlayer( std::string name, Ogre::ColourValue colour, unsigned long int signature);
		~NeuroPlayer(void);

	};

}