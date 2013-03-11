#include <Pulse.h>


#pragma once
namespace np
{
	class PulseFeed;

	class PulseGate
	{
	public:

		

		bool isConnected;

		double position;

		PulseFeed* target;

		PulseGate( double position)
		{
			this->position = position;
			isConnected = false;
		}

		~PulseGate(void)
		{
		}		

		bool operator < (const PulseGate& conn) const
		{
			return (position < conn.position);
		}

		void inputPulse( np::Pulse* pulse);

		void outputPulse( np::Pulse* pulse);

		void connect(PulseFeed* feed);

		void disconnect();

	};
}