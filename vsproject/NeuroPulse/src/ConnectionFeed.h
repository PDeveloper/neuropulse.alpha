#include <PulseComponent.h>

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

		virtual void inputPulse( np::PulseComponent* pulse)
		{
		}

		virtual void outputPulse( np::PulseComponent* pulse)
		{
		}

		bool operator < (const ConnectionFeed& conn) const
		{
			return (position < conn.position);
		}
	};
}