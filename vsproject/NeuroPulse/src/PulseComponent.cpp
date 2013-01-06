#include <PulseComponent.h>
#include <ConnectionComponent.h>

np::PulseComponent::PulseComponent( double energy, np::ConnectionComponent* connection)
{
	this->energy = energy;
	this->connection = connection;
}

np::PulseComponent::~PulseComponent(void)
{
}

double np::PulseComponent::get( double requestedEnergy)
{
	if ( requestedEnergy < energy)
	{
		energy -= requestedEnergy;
		return requestedEnergy;
	}
	else
	{
		energy = 0.0;
		// Must notify shit that this pulse was just destroyed.
		return energy;
	}
}

double np::PulseComponent::getPercent( double rate)
{
	double n_energy = energy * rate;
	energy -= n_energy;

	return n_energy;
}