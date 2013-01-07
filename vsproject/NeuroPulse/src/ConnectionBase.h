#include <NodeComponent.h>
#include <PulseComponent.h>
#include <ConnectionFeed.h>

#include <algorithm>
#include <list>
#include <math.h>

#pragma once
namespace np
{
	class ConnectionBase
	{
	public:

		np::NodeComponent* node;
		np::ConnectionBase* target;

		std::list<np::ConnectionFeed*> feeds;

		std::list<np::PulseComponent*> inPulseBuffer;

		ConnectionBase( np::NodeComponent* node)
		{
			this->node = node;
		}

		~ConnectionBase(void)
		{
		}

		void connect( np::ConnectionBase* target)
		{
			this->target = target;
		}

		void outputPulse( np::PulseComponent* pulse)
		{
			for (std::list<np::ConnectionFeed*>::iterator it = feeds.begin(); it != feeds.end(); it++)
				(*it)->outputPulse( pulse);
		}

		void inputPulse( np::PulseComponent* pulse)
		{
			for (std::list<np::ConnectionFeed*>::iterator it = feeds.end(); it != feeds.begin(); it--)
				(*it)->inputPulse( pulse);
		}

		void addFeed( np::ConnectionFeed* feed)
		{
			feeds.push_back( feed);
			feeds.sort();
		}

		void removeFeed( np::ConnectionFeed* feed)
		{
			for (std::list<np::ConnectionFeed*>::iterator it = feeds.begin(); it != feeds.end(); it++)
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