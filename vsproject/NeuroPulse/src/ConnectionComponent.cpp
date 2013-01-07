#include <ConnectionComponent.h>
#include <NodeComponent.h>
#include <PulseComponent.h>

np::ConnectionComponent::ConnectionComponent( np::ConnectionComponent* target)
{
	this->target = target;
}

np::ConnectionComponent::~ConnectionComponent(void)
{
}