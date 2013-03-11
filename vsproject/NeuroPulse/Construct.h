#include <vector>
#include <string>

#pragma once
namespace np
{
	class PulseGate;
	class ConstructInput;
	class ConstructOutput;
	class Pulse;
	class ConstructComponent;

	class Construct
	{
	public:

		std::vector<np::ConstructInput*> inputs;
		std::vector<np::ConstructOutput*> outputs;
		std::vector<np::PulseFeed*> pulseFeeds;

		np::ConstructComponent* constructComponent;


		virtual void processIncoming(np::Pulse* pulse) = 0;
		virtual void processOutgoing(np::Pulse* pulse) = 0;

		virtual std::string getName() = 0;
		virtual std::string getDescription() = 0;
		
	};
}
