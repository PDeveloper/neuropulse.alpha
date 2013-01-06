#include <ac\es.h>
#include <list>
#include <vector>

#include <math.h>

#include <ConnectionComponent.h>
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

		std::vector<np::ConnectionComponent*> connections;

		// Global pulse listeners
		std::list<IListener<PulseComponent>*> listeners;

		OutputComponent( ConnectionComponent* connections[]);
		~OutputComponent(void);

		void dispatch( PulseComponent& pulse);
		void addListener( IListener<PulseComponent> * listener);

	};

}