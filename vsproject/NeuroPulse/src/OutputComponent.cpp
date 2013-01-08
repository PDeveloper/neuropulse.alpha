#include <OutputComponent.h>

np::OutputComponent::OutputComponent(void)
	: connections()
{
}

np::OutputComponent::~OutputComponent(void)
{
}

void np::OutputComponent::addConnection( np::ConnectionBase* base)
{
	connections.push_back( base);
}

bool np::OutputComponent::hasConnection( np::NodeComponent* node)
{
	for ( int i = 0; i < connections.size(); i++)
	if ( connections.at(i)->target->node == node) return true;

	return false;
}