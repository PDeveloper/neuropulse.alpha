#pragma once

#include <ac\es.h>

#include <vector>

namespace np
{

	class NeuroWorld
	{
	public:

		std::vector<ac::es::EntityPtr> nodes;

		NeuroWorld(void);
		~NeuroWorld(void);
	};

}