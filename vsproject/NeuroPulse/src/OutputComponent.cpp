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

void np::OutputComponent::removeConnection( np::ConnectionBase* base )
{
	for (std::vector<np::ConnectionBase*>::iterator it = connections.begin(); it != connections.end(); it++)
		if ( (*it) == base)
		{
			connections.erase(it);
			return;
		}
}

bool np::OutputComponent::hasConnection( np::NodeComponent* node)
{
	for ( int i = 0; i < connections.size(); i++)
		if ( connections.at(i)->target->node == node) return true;

	return false;
}

np::ConnectionBase* np::OutputComponent::getConnection( ac::es::EntityPtr e)
{
	for ( int i = 0; i < connections.size(); i++)
		if ( connections[i]->target->parent == e) return connections[i];

	return NULL;
}
