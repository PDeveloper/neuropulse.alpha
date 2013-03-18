#include <ConstructComponent.h>

np::ConstructComponent::ConstructComponent(np::Construct* construct)
{
	this->construct = construct;
}

np::ConstructComponent::~ConstructComponent(void)
{
}

void np::ConstructComponent::setConstruct( np::Construct* construct )
{
	this->construct = construct;
}
