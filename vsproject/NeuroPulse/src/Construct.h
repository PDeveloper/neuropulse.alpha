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
#include "ConstructComponent.h"
namespace np
{

	class PulseFeed;
	class ConstructInput;
	class ConstructOutput;

	class Construct
	{
	public:

		np::ConstructComponent* container;

		std::vector<ac::es::EntityPtr> inputs;
		std::vector<ac::es::EntityPtr> outputs;

		std::vector<np::ResourceRequirement> inputRequirements;
		std::vector<np::ResourceRequirement> outputRequirements;

		Ogre::ColourValue colour;

		np::ComponentInterface* componentInterface;


		virtual void process() = 0;
		virtual void processInstructions(np::ResourcePacket* packet) = 0;

		virtual std::string getName() = 0;
		virtual std::string getDescription() = 0;

		virtual np::Construct* getUpgrade() = 0;

		void setContainer( np::ConstructComponent* container)
		{
			this->container = container;
		}

		Construct(Ogre::ColourValue colour) :
			colour( colour)
		{
		}

		virtual np::Construct* getNewInstance() = 0;


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
