#include <ac\es.h>
#include <GameObjectFactory.h>

#pragma once
namespace np
{
	class OutputSystem : public ac::es::EntityProcessingSystem
	{
		AC_ES_ENTITY_SYSTEM(OutputSystem)
	public:

		np::GameObjectFactory* gameObjectFactory;

		OutputSystem( np::GameObjectFactory* gameObjectFactory);
		~OutputSystem(void);

	protected:
		virtual void process( ac::es::EntityPtr e);
	};
}