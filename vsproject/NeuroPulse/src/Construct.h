#include <vector>
#include <string>

#include <Pulse.h>
#include <ResourceType.h>
#include <ResourceRequirement.h>
#include <ResourceManager.h>
#include <ac/es.h>
#include <OgreColourValue.h>

#include <BufferComponent.h>

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

		virtual void process() = 0;
		virtual void processInstructions(np::ResourcePacket* packet) = 0;

		virtual std::string getName() = 0;
		virtual std::string getDescription() = 0;

		Construct(Ogre::ColourValue colour) :
			colour( colour)
		{
		}

	protected:

		bool isEmpty( int input)
		{
			np::BufferComponent* buffer = inputs.at( input)->getComponent<np::BufferComponent>();

			return buffer->isEmpty();
		}

		np::BufferComponent* getInputBuffer( int input)
		{
			return inputs.at( input)->getComponent<np::BufferComponent>();
		}

		np::BufferComponent* getOutputBuffer( int output)
		{
			return outputs.at( output)->getComponent<np::BufferComponent>();
		}

		double getOutputLeft( int output)
		{
			return outputs.at( output)->getComponent<np::BufferComponent>()->getNormalSpaceLeft();
		}

		np::ResourcePacket* getPacketOf( np::ResourceType* type, double amount)
		{
			np::ResourcePacket* finalPacket = new np::ResourcePacket( type, 0.0);

			std::vector<ac::es::EntityPtr>::iterator i;
			for ( i = inputs.begin(); i != inputs.end(); ++i)
			{
				np::BufferComponent* buffer = (*i)->getComponent<np::BufferComponent>();
				np::ResourcePacket* packet = buffer->getPacket( type, amount);

				finalPacket->amount += packet->amount;
				amount -= packet->amount;

				if ( amount == 0.0) break;
			}

			return finalPacket;
		}

		np::ResourcePacket* getPacketOf( int input)
		{
			np::BufferComponent* buffer = inputs.at( input)->getComponent<np::BufferComponent>();

			return buffer->getPacket();
		}

		np::TransferSuccess putPacket( int output, np::ResourcePacket* packet)
		{
			np::BufferComponent* buffer = outputs.at( output)->getComponent<np::BufferComponent>();

			return buffer->appendPacket( packet);
		}
	};
}
