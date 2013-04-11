#include <vector>
#include <string>

#include <Pulse.h>
#include <ResourceType.h>
#include <ResourceRequirement.h>
#include <ResourceManager.h>
#include <ac/es.h>
#include <OgreColourValue.h>

#include <BufferComponent.h>
#include <ComponentInterface.h>

#pragma once
namespace np
{

	class Construct
	{
	public:

		std::vector<ac::es::EntityPtr> inputs;
		std::vector<ac::es::EntityPtr> outputs;

		std::vector<np::ResourceRequirement> inputRequirements;
		std::vector<np::ResourceRequirement> outputRequirements;

		Ogre::ColourValue colour;

		np::ComponentInterface* componentInterface;

		bool getOn()
		{
			return isOn;
		}

		void setOn(bool val)
		{
			isOn = val;
		}

		virtual void process() = 0;
		virtual void processInstructions(np::ResourcePacket* packet) = 0;

		virtual std::string getName() = 0;
		virtual std::string getDescription() = 0;

		Construct()
		{
		}

	protected:
		bool isEmpty( int input)
		{
			np::BufferComponent* buffer = inputs.at( input)->getComponent<np::BufferComponent>();

			return buffer->isEmpty();
		}

		np::ResourcePacket* getNextPacket( np::ResourceRequirement requirement)
		{
			std::vector<ac::es::EntityPtr>::iterator i;

			for ( i = inputs.begin(); i != inputs.end(); ++i)
			{
				np::BufferComponent* buffer = (*i)->getComponent<np::BufferComponent>();
				np::ResourcePacket* packet = buffer->getNextPacketOf( &requirement);

				if ( packet != NULL) return packet;
			}

			return NULL;
		}

		np::ResourcePacket* getNextPacket( int input)
		{
			np::BufferComponent* buffer = inputs.at( input)->getComponent<np::BufferComponent>();

			return buffer->getPacket();
		}

		bool putPacket( int output, np::ResourcePacket* packet)
		{
			np::BufferComponent* buffer = outputs.at( output)->getComponent<np::BufferComponent>();

			return buffer->addPacket( packet);
		}

	protected:
		bool isOn;
	};
}
