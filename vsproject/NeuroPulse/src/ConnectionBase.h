#include <ac\es.h>

#include <NodeComponent.h>
#include <BufferComponent.h>
#include <PulseGateComponent.h>

#include <ResourceInputComponent.h>
#include <ResourceOutputComponent.h>

#include <Pulse.h>
#include <PulseGateSlot.h>

#include <algorithm>
#include <list>
#include <math.h>

#pragma once
#include "AdvancedOgreFramework.hpp"
namespace np
{
	class ConnectionBase
	{
	public:

		ac::es::EntityPtr parent;

		np::NodeComponent* node;
		np::ConnectionBase* target;

		std::list<np::PulseGateSlot*> pulseGates;

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

			std::list<np::PulseGateSlot*>::iterator it;
			for ( it = pulseGates.begin(); it != pulseGates.end(); it++)
			{
				ac::es::EntityPtr e = (*it)->pulseGate;
				np::BufferComponent* buffer = e->getComponent<np::BufferComponent>();
				np::ResourceInputComponent* input = e->getComponent<np::ResourceInputComponent>();
				np::ResourceOutputComponent* output = e->getComponent<np::ResourceOutputComponent>();

				if ( input != NULL)
				{
					std::list<np::ResourcePacket*> packets = buffer->getPackets();
					if ( pulseBuffer->addPackets( &packets) == PARTIAL) buffer->addPackets( &packets);
				}

				if ( output != NULL)
				{
					std::list<np::ResourcePacket*> packets = pulseBuffer->getPackets();
					if ( buffer->addPackets( &packets) == PARTIAL) pulseBuffer->addPackets( &packets);
				}
			}
		}

		void inputPulse( ac::es::EntityPtr pulseEntity)
		{
			np::BufferComponent* pulseBuffer = pulseEntity->getComponent<np::BufferComponent>();

			std::list<np::PulseGateSlot*>::iterator it;
			for ( it = pulseGates.begin(); it != pulseGates.end(); it++)
			{
				ac::es::EntityPtr e = (*it)->pulseGate;
				np::BufferComponent* buffer = e->getComponent<np::BufferComponent>();
				np::ResourceInputComponent* input = e->getComponent<np::ResourceInputComponent>();
				np::ResourceOutputComponent* output = e->getComponent<np::ResourceOutputComponent>();

				if ( input != NULL)
				{
					std::list<np::ResourcePacket*> packets = buffer->getPackets();
					if ( pulseBuffer->addPackets( &packets) == PARTIAL) buffer->addPackets( &packets);
				}

				if ( output != NULL)
				{
					std::list<np::ResourcePacket*> packets = pulseBuffer->getPackets();
					if ( buffer->addPackets( &packets) == PARTIAL) pulseBuffer->addPackets( &packets);
				}
			}
		}

		void addFeed( ac::es::EntityPtr pulseGate)
		{
			if ( pulseGate->getComponent<np::PulseGateComponent>() != NULL)
			{
				pulseGates.push_back( new np::PulseGateSlot( pulseGate));
				pulseGates.sort();
			}
		}

		void removeFeed( ac::es::EntityPtr pulseGate)
		{
			np::PulseGateSlot* slot;
			std::list<np::PulseGateSlot*>::iterator it;

			it = pulseGates.begin();
			while ( it != pulseGates.end())
			{
				slot = *it;
				if ( slot->pulseGate == pulseGate)
				{
					OgreFramework::getSingletonPtr()->m_pLog->logMessage( "PulseGate removed");

					pulseGates.erase( it++);
					delete slot;
				}
				else
				{
					++it;
				}
			}
		}

	};
}