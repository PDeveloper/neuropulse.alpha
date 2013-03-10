#pragma once

namespace np
{
	class PulseSystemSettings
	{
	public:

		double globalPulseTime;

		PulseSystemSettings( double globalPulseTime);
		~PulseSystemSettings(void);
	};

}