#include <ac\es.h>

#include <vector>
#include <NeuroPlayer.h>

#pragma once
namespace np
{

	class NeuroWorld
	{
	public:

		np::NeuroPlayer* player;

		std::vector<ac::es::EntityPtr> nodes;

		NeuroWorld(void);
		~NeuroWorld(void);
	};

}