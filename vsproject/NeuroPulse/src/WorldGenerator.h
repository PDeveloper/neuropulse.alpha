#include <GameObjectFactory.h>
#include <NeuroWorld.h>
#include <NeuroWorldSettings.h>

#pragma once
namespace np
{
	class WorldGenerator
	{
	public:

		WorldGenerator(void);
		~WorldGenerator(void);

		void generateWorld( np::NeuroWorld* neuroWorld);
		void generateWorld2( np::NeuroWorld* neuroWorld);
	};
}