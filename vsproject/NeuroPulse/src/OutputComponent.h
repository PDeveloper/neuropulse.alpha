#include <ac\es.h>
#include <list>
#include <vector>

#include <math.h>

#include <ConnectionBase.h>
#include <PulseComponent.h>
#include <NodeComponent.h>

#include <IListener.h>

/**
	ReactionComponent
	Since not all nodes will have a constant increase in energy, this component handles the increase. Add it to live nodes, dead nodes just
	don't have it.
**/

#pragma once
namespace np
{
	class OutputComponent :
		public ac::es::Component
	{
		AC_ES_COMPONENT(OutputComponent)
	public:

		// connection bases
		std::vector<np::ConnectionBase*> connections;

		OutputComponent( ConnectionBase* connections[]);
		~OutputComponent(void);

	};

}