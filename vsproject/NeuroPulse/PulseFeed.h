#include <Pulse.h>


#pragma once
namespace np
{
	class PulseGate;
	class Construct;

	class PulseFeed
	{
	public:

		PulseGate* target;

		Construct* construct; 

		bool isConnected;

		PulseFeed(Construct* construct)
		{
			isConnected = false;
			this->construct = construct;
		}

		~PulseFeed(void)
		{
		}		

		void inputPulse( np::Pulse* pulse);

		void outputPulse( np::Pulse* pulse);

		void connect(PulseGate* gate);

		void disconnect();
	};
}