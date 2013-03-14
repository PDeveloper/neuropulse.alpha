#include <vector>
#include <string>

#include <ConstructInput.h>
#include <ConstructOutput.h>
#include <PulseGate.h>

#include <Pulse.h>
#include <ResourceType.h>

#include <OgreColourValue.h>

#pragma once
namespace np
{

	class Construct
	{
	public:

		std::vector<np::ConstructInput*> inputs;
		std::vector<np::ConstructOutput*> outputs;
		std::vector<np::PulseFeed*> pulseFeeds;

		Ogre::ColourValue colour;

		virtual void processIncoming(np::Pulse* pulse) = 0;
		virtual void processOutgoing(np::Pulse* pulse) = 0;
		virtual void update(void) = 0;

		virtual std::string getName() = 0;
		virtual std::string getDescription() = 0;
		
	};
}
