#include <HubComponent.h>
#include <ConstructComponent.h>

np::HubComponent::HubComponent( np::NeuroPlayer* owner) :
	constructs()
{
	this->owner = owner;

	health = 100.0;
	
	overheatTemperature = 3500;
	overheatDamage = 0.05;
}

np::HubComponent::~HubComponent(void)
{

}

void np::HubComponent::destroy()
{
	//Explode or some fancy shit like that
}
