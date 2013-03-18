#include <HubComponent.h>
#include <ConstructComponent.h>

np::HubComponent::HubComponent( np::NeuroPlayer* owner) :
	constructs()
{
	this->owner = owner;

	health = 100.0;
}

np::HubComponent::~HubComponent(void)
{

}