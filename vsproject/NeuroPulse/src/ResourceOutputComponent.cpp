#include "ResourceOutputComponent.h"

#include <ResourceInputComponent.h>


np::ResourceOutputComponent::ResourceOutputComponent(void)
{
}


np::ResourceOutputComponent::~ResourceOutputComponent(void)
{
}

bool np::ResourceOutputComponent::connect( ac::es::EntityPtr target )
{
	if ( target->containsComponent<np::ResourceInputComponent>())
	{
		this->target = target;

		return true;
	}

	return false;
}

