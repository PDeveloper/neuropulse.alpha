#include "ResourceInputComponent.h"

#include <ResourceOutputComponent.h>


np::ResourceInputComponent::ResourceInputComponent(void)
{
}


np::ResourceInputComponent::~ResourceInputComponent(void)
{
}

bool np::ResourceInputComponent::connect( ac::es::EntityPtr target )
{
	if ( target->containsComponent<np::ResourceOutputComponent>())
	{
		this->target = target;

		return true;
	}

	return false;
}
