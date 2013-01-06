#include <OutputComponent.h>

np::OutputComponent::OutputComponent( ConnectionComponent* connections[])
	: connections( connections, connections + sizeof(connections) / sizeof(connections[0]) )
{
			
}

np::OutputComponent::~OutputComponent(void)
{
}

void np::OutputComponent::dispatch( PulseComponent& pulse)
{
	for (std::list<IListener<PulseComponent>*>::iterator it = listeners.begin(); it != listeners.end(); it++)
		(*it)->dispatchListener( pulse);
}

void np::OutputComponent::addListener( IListener<PulseComponent> * listener)
{
	listeners.push_back( listener);
}