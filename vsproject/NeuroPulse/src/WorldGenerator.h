#include <GameObjectFactory.h>

#pragma once
namespace np
{
	class WorldGenerator
	{
	public:
		WorldGenerator(void);
		~WorldGenerator(void);

		void generateWorld( np::GameObjectFactory* factory, const int numNodes);
		void generateWorld2( np::GameObjectFactory* factory, const int numNodes);
	};
}