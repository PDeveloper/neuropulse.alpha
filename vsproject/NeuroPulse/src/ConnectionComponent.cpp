#include <ConnectionComponent.h>
#include <NodeComponent.h>
#include <PulseComponent.h>

np::ConnectionComponent::ConnectionComponent( np::TransformComponent* target1, np::TransformComponent* target2)
{
	this->target1 = target1;
	this->target2 = target2;
}

np::ConnectionComponent::~ConnectionComponent(void)
{
}