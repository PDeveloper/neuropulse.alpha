#include "ConstructUpgradeSystem.h"
#include "ConstructComponent.h"
#include "Construct.h"

np::ConstructUpgradeSystem::ConstructUpgradeSystem(GameObjectFactory* gameObjectFactory) :
	ac::es::EntityProcessingSystem( ac::es::ComponentFilter::Requires<ConstructComponent>())
{
	this->objectFactory = gameObjectFactory;
}

np::ConstructUpgradeSystem::~ConstructUpgradeSystem()
{

}

void np::ConstructUpgradeSystem::process( ac::es::EntityPtr e )
{
	ConstructComponent* constructComponent = e->getComponent<ConstructComponent>();

	if ( constructComponent == NULL) return;
	if ( constructComponent->construct != NULL)
	{
		Construct* upgrade = constructComponent->construct->getUpgrade();

		//It's upgrade time, come on, grab your friends
		if(upgrade != NULL)
		{
			objectFactory->removeConstruct(e, constructComponent->construct);
			objectFactory->setConstruct(e, upgrade);
		}
	}
}

