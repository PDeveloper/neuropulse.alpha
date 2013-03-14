#pragma once
namespace np
{
	class NeuroWorldSettings
	{
	public:

		double globalPulseTime;

		int numberOfNodes;
		double mapWidth;
		double mapHeight;
	
		NeuroWorldSettings(void)
		{
			globalPulseTime = 800;
			numberOfNodes = 20;

			mapWidth = 1200.0;
			mapHeight = 1200.0;
		}
	
		~NeuroWorldSettings(void)
		{
		}
	};
}

