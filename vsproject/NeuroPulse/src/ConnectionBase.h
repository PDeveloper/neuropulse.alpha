#include <ac\es.h>

#include <NodeComponent.h>
#include <PulseGate.h>

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

		std::list<np::PulseGate*> feeds;

		std::list<np::Pulse*> inPulseBuffer;

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

		void outputPulse( np::Pulse* pulse)
		{
			for (std::list<np::PulseGate*>::iterator it = feeds.begin(); it != feeds.end(); it++)
				(*it)->outPulse( pulse);
		}

		void inputPulse( np::Pulse* pulse)
		{
			for (std::list<np::PulseGate*>::iterator it = feeds.end(); it != feeds.begin(); it--)
				(*it)->inPulse( pulse);
		}

		void addFeed( np::PulseGate* feed)
		{
			feeds.push_back( feed);
			feeds.sort();
		}

		void removeFeed( np::PulseGate* feed)
		{
			for (std::list<np::PulseGate*>::iterator it = feeds.begin(); it != feeds.end(); it++)
			if ( (*it) == feed)
			{
				feeds.erase(it);
				return;
			}
		}

		double resistance()
		{
			return std::max<double>( target->node->currentEnergy, target->node->energyThreshold);
		}

		bool isValid()
		{
			return node->currentEnergy > resistance();
		}
	};
}