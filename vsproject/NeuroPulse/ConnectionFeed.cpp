#include "ConnectionFeed.h"
#include "ConstructComponent.h"
#include "ConstructProcessing.h"

void np::ConnectionFeed::inputPulse(np::Pulse* pulse)
{
	construct->constructProcessing->processIncoming(pulse);
}

void np::ConnectionFeed::outputPulse(np::Pulse* pulse)
{
	construct->constructProcessing->processOutgoing(pulse);
}