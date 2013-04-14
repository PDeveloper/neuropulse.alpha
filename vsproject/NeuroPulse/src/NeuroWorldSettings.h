#include <vector>
#include <string>

#include <NeuroPlayer.h>

#pragma once
namespace np
{
	class NeuroWorldSettings
	{
	public:

		double globalPulseTime;

		int numberOfNodes;
		double mapWidth;
		double mapHeight;

		std::vector<np::NeuroPlayer*> players;
		
		NeuroWorldSettings(void) :
			players()
		{
			globalPulseTime = 800;
			numberOfNodes = 20;

			mapWidth = 1200.0;
			mapHeight = 1200.0;
		}
	
		~NeuroWorldSettings(void)
		{
			std::vector<np::NeuroPlayer*>::iterator it;

			for ( it = players.begin(); it < players.end(); ++it)
			{
				delete (*it);
			}
		}
		
		void addPlayer( std::string name, Ogre::ColourValue colour)
		{
			players.push_back( new np::NeuroPlayer( name, colour, 1 << players.size()));
		}

		np::NeuroPlayer* getPlayerFromSignature( unsigned long int signature)
		{
			for ( int i = 0; i < 32; i++)
			{
				if ( ( 1 << i) == signature) return players[i];
			}

			return NULL;
		}
	};
}

