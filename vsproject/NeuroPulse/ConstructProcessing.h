#include <vector>
#include "ConstructConnectionBase.h"
#include "Pulse.h"
#include "ConnectionFeed.h"

#pragma once
namespace np
{
	class ConstructProcessing
	{
		


		virtual void processIncoming(np::Pulse* pulse);
		virtual void processOutgoing(np::Pulse* pulse);

		virtual np::ConstructConnectionBase* getInput(int i);
		virtual np::ConstructConnectionBase* getOutput(int i);
	};
}
