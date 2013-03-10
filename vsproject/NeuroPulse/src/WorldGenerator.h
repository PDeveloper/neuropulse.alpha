#include <GameObjectFactory.h>
#include <NeuroWorld.h>

#pragma once
namespace np
{
	class WorldGenerator
	{
	public:
		WorldGenerator(void);
		~WorldGenerator(void);

		void generateWorld( np::NeuroWorld* neuroWorld, np::GameObjectFactory* factory, const int numNodes);
		void generateWorld2( np::NeuroWorld* neuroWorld, np::GameObjectFactory* factory, const int numNodes);
	};
}