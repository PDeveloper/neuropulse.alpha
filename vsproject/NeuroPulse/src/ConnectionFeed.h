#include <Pulse.h>

#pragma once
namespace np
{
	class ConnectionFeed
	{
	public:

		double position;

		ConnectionFeed( double position)
		{
			this->position = position;
		}

		~ConnectionFeed(void)
		{
		}

		virtual void inputPulse( np::Pulse* pulse)
		{
		}

		virtual void outputPulse( np::Pulse* pulse)
		{
		}

		bool operator < (const ConnectionFeed& conn) const
		{
			return (position < conn.position);
		}
	};
}