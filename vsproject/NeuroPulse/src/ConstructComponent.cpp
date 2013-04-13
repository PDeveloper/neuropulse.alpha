#include <ConstructComponent.h>
#include <Construct.h>

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
	if ( construct == NULL) this->construct->setContainer( NULL);
	this->construct = construct;
	if ( construct != NULL) construct->setContainer( this);
}
