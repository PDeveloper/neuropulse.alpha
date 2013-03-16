#include <Pulse.h>


#pragma once
namespace np
{

	class ConstructInput;
	class ConstructOutput;

	class PulseGate
	{
	public:

		static const int MODE_OUTPUT = 0;
		static const int MODE_INPUT = 1;

		int mode;

		bool isConnected;

		double position;

		ConstructInput* input;
		ConstructOutput* output;

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

		void inPulse( np::Pulse* pulse);

		void outPulse( np::Pulse* pulse);

		void connect(ConstructInput* input);
		void connect(ConstructOutput* output);

		void disconnect();

	};
}