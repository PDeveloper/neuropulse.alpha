#include <vector>
#include "ConstructInput.h"
#include "ConstructOutput.h"
#include "Pulse.h"
//#include "ConnectionFeed.h"

#pragma once
namespace np
{
	class ConnectionFeed;


	class ConstructProcessing
	{
	public:

		std::vector<ConstructInput*> inputs;
		std::vector<ConstructOutput*> outputs;
		std::vector<ConnectionFeed*> connectionFeeds;

		ConstructComponent* constructComponent;


		virtual void processIncoming(np::Pulse* pulse);
		virtual void processOutgoing(np::Pulse* pulse);

		virtual np::ConstructInput* getInput(int i);
		virtual np::ConstructOutput* getOutput(int i);
	};
}
