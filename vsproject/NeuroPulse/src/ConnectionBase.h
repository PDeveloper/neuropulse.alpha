#include <ac\es.h>

#include <NodeComponent.h>
#include <BufferComponent.h>
#include <PulseGateComponent.h>

#include <ResourceInputComponent.h>
#include <ResourceOutputComponent.h>

#include <Pulse.h>

#include <algorithm>
#include <list>
#include <math.h>

#pragma once
namespace np
{
	class ConnectionBase
	{
	public:

		ac::es::EntityPtr parent;

		np::NodeComponent* node;
		np::ConnectionBase* target;

		std::list<ac::es::EntityPtr> feeds;

		std::vector<ac::es::EntityPtr> outputPulses;

		ConnectionBase( ac::es::EntityPtr parent)
		{
			this->parent = parent;
			this->node = parent->getComponent<np::NodeComponent>();
		}

		~ConnectionBase(void)
		{
		}

		void connect( np::ConnectionBase* target)
		{
			this->target = target;
			target->target = this;
		}

		void outputPulse( ac::es::EntityPtr pulseEntity)
		{
			np::BufferComponent* pulseBuffer = pulseEntity->getComponent<np::BufferComponent>();

			for (std::list<ac::es::EntityPtr>::iterator it = feeds.begin(); it != feeds.end(); it++)
			{
				ac::es::EntityPtr e = *it;
				np::BufferComponent* buffer = e->getComponent<np::BufferComponent>();
				np::ResourceInputComponent* input = e->getComponent<np::ResourceInputComponent>();

				if ( input != NULL)
				{
					std::list<np::ResourcePacket*> packets = buffer->getPackets();

					if ( pulseBuffer->addPackets( &packets) == PARTIAL) buffer->addPackets( &packets);
				}
			}
		}

		void inputPulse( ac::es::EntityPtr pulseEntity)
		{
			np::BufferComponent* pulseBuffer = pulseEntity->getComponent<np::BufferComponent>();

			for (std::list<ac::es::EntityPtr>::iterator it = feeds.end(); it != feeds.begin(); it--)
			{
				ac::es::EntityPtr e = *it;
				np::BufferComponent* buffer = e->getComponent<np::BufferComponent>();
				np::ResourceOutputComponent* output = e->getComponent<np::ResourceOutputComponent>();

				if ( output != NULL)
				{

				}
			}
		}

		void addFeed( ac::es::EntityPtr feed)
		{
			if ( feed->getComponent<np::PulseGateComponent>() != NULL)
			{
				feeds.push_back( feed);
				feeds.sort();
			}
		}

		void removeFeed( ac::es::EntityPtr feed)
		{
			feeds.remove( feed);
		}

	};
}