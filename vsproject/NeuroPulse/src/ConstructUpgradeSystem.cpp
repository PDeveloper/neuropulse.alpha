#include "ConstructUpgradeSystem.h"
#include "ConstructComponent.h"
#include "Construct.h"
#include <AdvancedOgreFramework.hpp>

#include <OgreOggSound.h>
#include "GraphicComponent.h"

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
			OgreFramework::getSingletonPtr()->m_pLog->logMessage( "Removing");

			objectFactory->removeConstruct(e, constructComponent->construct);

			OgreFramework::getSingletonPtr()->m_pLog->logMessage( "Adding");
			objectFactory->setConstruct(e, upgrade);

			OgreOggSound::OgreOggISound* sound = OgreOggSound::OgreOggSoundManager::getSingletonPtr()->getSound( "ConstructBuilt");
			sound->setPlayPosition( 0.0);
			sound->setPosition( e->getComponent<np::GraphicComponent>()->node->_getDerivedPosition());
			sound->play();
		}
	}
}

