#include <ConnectionComponent.h>
#include <NodeComponent.h>
#include <PulseComponent.h>

np::ConnectionComponent::ConnectionComponent( np::NodeComponent* node1, np::NodeComponent* node2)
{
	this->node1 = node1;
	this->node2 = node2;
}

np::ConnectionComponent::~ConnectionComponent(void)
{
}

np::NodeComponent* np::ConnectionComponent::getOtherNode( np::NodeComponent* node)
{
	if ( node == node1) return node2;
	else if ( node == node2) return node1;

	return NULL;
}