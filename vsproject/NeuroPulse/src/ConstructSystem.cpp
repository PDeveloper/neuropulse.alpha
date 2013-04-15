#include "ConstructSystem.h"
#include "ConstructComponent.h"
#include "Construct.h"

np::ConstructSystem::ConstructSystem() :
	ac::es::EntityProcessingSystem( ac::es::ComponentFilter::Requires<ConstructComponent>())
{
	deltaTime = 0;
}

np::ConstructSystem::~ConstructSystem()
{

}

void np::ConstructSystem::setDeltaTime( double time)
{
	deltaTime = time;
}

void np::ConstructSystem::process( ac::es::EntityPtr e )
{
	ConstructComponent* constructComponent = e->getComponent<ConstructComponent>();

	if ( constructComponent == NULL) return;
	if ( constructComponent->construct != NULL)
	{
		constructComponent->construct->process(deltaTime);

	}
}

