#include <ac\es.h>

#pragma once
namespace np
{
	class WorldGenerator
	{
	public:
		WorldGenerator(void);
		~WorldGenerator(void);

		void generateWorld( ac::es::Scene* scene);
	};
}