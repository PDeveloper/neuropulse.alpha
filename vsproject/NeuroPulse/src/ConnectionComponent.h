#include <ac\es.h>
#include <list>

/**
	ConnectionComponent
	This component handles all data traveling between 2 different NodeComponents. This includes distance.
	Not sure if this component can be totally replaced by a system, since this component needs access to NodeComponent and a TransformComponent
	Maybe it adds entities...but better would be to keep everything with components.

	Still not sure on event management etc.
**/

#pragma once
namespace np
{
	class NodeComponent;
	class PulseComponent;

	class ConnectionComponent :
		public ac::es::Component
	{
		AC_ES_COMPONENT(ConnectionComponent)
	public:

		np::ConnectionComponent* target;

		std::list<np::PulseComponent> pulses;

		ConnectionComponent( np::ConnectionComponent* target);
		~ConnectionComponent(void);
		
	};
}