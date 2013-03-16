#include "ConstructConnectionSystem.h"
#include "ConstructComponent.h"
#include "Construct.h"




void np::ConstructConnectionSystem::process( ac::es::EntityPtr e )
{
	ConstructComponent* constructComponent = e->getComponent<ConstructComponent>();

	Construct* construct = constructComponent->construct;

	for(int i=0; i<construct->outputs.size(); i++)
	{
		construct->outputs.at(i)->send();
	}
}
