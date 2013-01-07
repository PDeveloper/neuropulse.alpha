#include <OutputComponent.h>

np::OutputComponent::OutputComponent( ConnectionBase* connections[])
	: connections( connections, connections + sizeof(connections) / sizeof(connections[0]) )
{
			
}

np::OutputComponent::~OutputComponent(void)
{
}