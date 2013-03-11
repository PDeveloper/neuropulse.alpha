#include "PulseGate.h"
#include "PulseFeed.h"
#include "ConstructComponent.h"
#include "Construct.h"

void np::PulseGate::inputPulse(np::Pulse* pulse)
{
	if(isConnected)
		target->inputPulse(pulse);
}

void np::PulseGate::outputPulse(np::Pulse* pulse)
{
	if(isConnected)
		target->outputPulse(pulse);
}

void np::PulseGate::connect(np::PulseFeed* target )
{
	this->target = target;
	this->isConnected = true;

	target->target = this;
	target->isConnected = true;
}

void np::PulseGate::disconnect()
{
	target->isConnected = false;
	this->isConnected = false;
}
