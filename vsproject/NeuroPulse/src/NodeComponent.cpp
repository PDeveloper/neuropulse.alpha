#include <NodeComponent.h>

np::NodeComponent::NodeComponent( double energyThreshold)
{
	this->energyThreshold = energyThreshold;

	currentEnergy = 0.0;
}

np::NodeComponent::~NodeComponent(void)
{

}