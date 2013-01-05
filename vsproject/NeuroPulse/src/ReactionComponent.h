#include <ac\es.h>

/**
	ReactionComponent
	Since not all nodes will have a constant increase in energy, this component handles the increase. Add it to live nodes, dead nodes just
	don't have it.
**/

#pragma once
namespace np
{
	class ReactionComponent :
		public ac::es::Component
	{
		AC_ES_COMPONENT(ReactionComponent)
	public:

		double output;

		ReactionComponent( double output)
		{
			this->output = output;
		}

		~ReactionComponent(void)
		{
		}
	};
}