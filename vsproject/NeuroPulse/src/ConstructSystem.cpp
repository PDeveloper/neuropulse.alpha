#include "ConstructSystem.h"
#include "ConstructComponent.h"
#include "Construct.h"

np::ConstructSystem::ConstructSystem() :
	ac::es::EntityProcessingSystem( ac::es::ComponentFilter::Requires<ConstructComponent>())
{

}

np::ConstructSystem::~ConstructSystem()
{

}

void np::ConstructSystem::process( ac::es::EntityPtr e )
{
	ConstructComponent* constructComponent = e->getComponent<ConstructComponent>();

	if ( constructComponent->construct != NULL) constructComponent->construct->process();
}

