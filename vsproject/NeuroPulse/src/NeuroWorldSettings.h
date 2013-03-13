#pragma once
namespace np
{
	class NeuroWorldSettings
	{
	public:

		double globalPulseTime;
		int numberOfNodes;
	
		NeuroWorldSettings(void)
		{
			globalPulseTime = 800;
			numberOfNodes = 9;
		}
	
		~NeuroWorldSettings(void)
		{
		}
	};
}

