#include <vector>
#include <string>

#include <ConstructInput.h>
#include <ConstructOutput.h>
#include <PulseGate.h>

#include <Pulse.h>
#include <ResourceType.h>
#include <ResourceManager.h>

#include <OgreColourValue.h>

#pragma once
namespace np
{

	class Construct
	{
	public:

		std::vector<np::ConstructInput*> inputs;
		std::vector<np::ConstructOutput*> outputs;

		Ogre::ColourValue colour;

		virtual void process() = 0;
		virtual void processInstructions(np::ResourcePacket* packet) = 0;

		virtual std::string getName() = 0;
		virtual std::string getDescription() = 0;
		
	};
}
