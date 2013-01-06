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

		OutputComponent( ConnectionComponent* connections[])
			: connections( connections, connections + sizeof(connections) / sizeof(connections[0]) )
		{
			
		}

		~OutputComponent(void)
		{
		}

		void dispatch( PulseComponent& pulse)
		{
			for (std::list<IListener<PulseComponent>*>::iterator it = listeners.begin(); it != listeners.end(); it++)
				(*it)->dispatchListener( pulse);
		}

		void addListener( IListener<PulseComponent> * listener)
		{
			listeners.push_back( listener);
		}

	};

}