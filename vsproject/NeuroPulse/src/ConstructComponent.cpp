#include <ConstructComponent.h>

np::ConstructComponent::ConstructComponent(np::Construct* construct, ac::es::EntityPtr parent)
{
	this->construct = construct;
	this->parent = parent;
}

np::ConstructComponent::~ConstructComponent(void)
{
}

void np::ConstructComponent::setConstruct( np::Construct* construct)
{
	this->construct = construct;
}
