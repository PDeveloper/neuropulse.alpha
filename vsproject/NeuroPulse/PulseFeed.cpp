#include "PulseGate.h"
#include "PulseFeed.h"
#include "ConstructComponent.h"
#include "Construct.h"

void np::PulseFeed::inputPulse(np::Pulse* pulse)
{
	construct->processIncoming(pulse);
}

void np::PulseFeed::outputPulse(np::Pulse* pulse)
{
	construct->processOutgoing(pulse);
}

void np::PulseFeed::connect(np::PulseGate* target )
{
	this->target = target;
	this->isConnected = true;

	target->target = this;
	target->isConnected = true;
}

void np::PulseFeed::disconnect()
{
	target->isConnected = false;
	this->isConnected = false;
}