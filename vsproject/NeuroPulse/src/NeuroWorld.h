#include <ac\es.h>

#include <vector>

#pragma once
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