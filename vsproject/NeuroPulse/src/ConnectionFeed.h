#include <Pulse.h>


#pragma once
namespace np
{
	//class ConstructComponent;

	class ConstructComponent;

	class ConnectionFeed
	{
	public:

		ConstructComponent* construct;

		double position;

		ConnectionFeed( double position)
		{
			this->position = position;
		}

		~ConnectionFeed(void)
		{
		}		

		bool operator < (const ConnectionFeed& conn) const
		{
			return (position < conn.position);
		}

		void inputPulse( np::Pulse* pulse);

		void outputPulse( np::Pulse* pulse);
	};
}