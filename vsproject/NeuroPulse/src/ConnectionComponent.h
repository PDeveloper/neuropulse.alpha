#include <ac\es.h>
#include <list>

#include <TransformComponent.h>

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

	class ConnectionComponent :
		public ac::es::Component
	{
		AC_ES_COMPONENT(ConnectionComponent)
	public:

		np::TransformComponent* target1;
		np::TransformComponent* target2;

		ConnectionComponent( np::TransformComponent* target1, np::TransformComponent* target2);
		~ConnectionComponent(void);
		
	};
}