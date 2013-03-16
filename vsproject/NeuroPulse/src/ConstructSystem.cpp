#include "ConstructSystem.h"
#include "ConstructComponent.h"
#include "Construct.h"

void np::ConstructSystem::process( ac::es::EntityPtr e )
{
	ConstructComponent* constructComponent = e->getComponent<ConstructComponent>();

	Construct* construct = constructComponent->construct;

	construct->process();

}

