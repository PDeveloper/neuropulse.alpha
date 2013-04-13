#include <ac\es.h>
#include <GameObjectFactory.h>

#pragma once
namespace np
{
	class ConstructUpgradeSystem : public ac::es::EntityProcessingSystem
	{
		AC_ES_ENTITY_SYSTEM(ConstructUpgradeSystem)
	public:



		ConstructUpgradeSystem(GameObjectFactory* gameObjectFactory);
		~ConstructUpgradeSystem(void);

		GameObjectFactory* objectFactory;

	protected:
		void process( ac::es::EntityPtr e);

	};
}