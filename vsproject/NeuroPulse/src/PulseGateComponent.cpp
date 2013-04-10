#include "PulseGateComponent.h"


np::PulseGateComponent::PulseGateComponent( int connection, double position, ac::es::EntityPtr nodeEntity)
{
	this->connection = connection;
	this->position = position;
	this->nodeEntity = nodeEntity;
}


np::PulseGateComponent::~PulseGateComponent(void)
{
}
