#include <NodeComponent.h>

np::NodeComponent::NodeComponent( double energyThreshold)
{
	this->energyThreshold = energyThreshold;

	currentEnergy = 0.0;

	heatDissipation = 0.1;
	heatCapacity = 1;
	temperature = 0;
}

np::NodeComponent::~NodeComponent(void)
{

}