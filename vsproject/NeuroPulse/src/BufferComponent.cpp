#include "BufferComponent.h"
#include <algorithm>
#include "AdvancedOgreFramework.hpp"

np::BufferComponent::BufferComponent( np::ResourceRequirement types, double size) :
	buffer(),
	types( types)
{
	totalSpace = size;
}

np::BufferComponent::~BufferComponent(void)
{
}

np::ResourceRequirement& np::BufferComponent::getTypes()
{
	return types;
}

double np::BufferComponent::getNormalSpaceLeft()
{
	double space = totalSpace;

	std::list<np::ResourcePacket*>::iterator i;
	for ( i = buffer.begin(); i != buffer.end(); ++i)
	{
		space -= (*i)->amount * (*i)->resourceType->weight();
	}

	return space;
}

double np::BufferComponent::getSpaceLeft( np::ResourceType* type)
{
	double space = totalSpace;

	std::list<np::ResourcePacket*>::iterator i;
	for ( i = buffer.begin(); i != buffer.end(); ++i)
	{
		space -= (*i)->amount * (*i)->resourceType->weight();
	}

	return space / type->weight();
}

np::TransferSuccess np::BufferComponent::addPacket( np::ResourcePacket* packet )
{
	if ( types.contains( packet->resourceType))
	{
		double spaceLeft = getSpaceLeft( packet->resourceType);
		
		if ( packet->amount < spaceLeft)
		{
			buffer.push_back( packet);

			return FULL;
		}
		else
		{
			packet->amount -= spaceLeft;
			buffer.push_back( new np::ResourcePacket( packet->resourceType, spaceLeft));
			
			return PARTIAL;
		}
	}
	else
	{
		return TYPE_CONFLICT;
	}
}

np::TransferSuccess np::BufferComponent::appendPacket( np::ResourcePacket* packet )
{
	if ( types.contains( packet->resourceType))
	{
		double spaceLeft = getSpaceLeft( packet->resourceType);
		
		std::list<np::ResourcePacket*>::iterator i = buffer.begin();
		while ( i != buffer.end())
		{
			if ( packet->resourceType == (*i)->resourceType && packet->signature == (*i)->signature)
			{
				double amount = std::min( packet->amount, spaceLeft);

				(*i)->amount += amount;
				packet->amount -= amount;

				if ( packet->amount == 0.0)
				{
					delete packet;
					return FULL;
				}
				else
				{
					return PARTIAL;
				}
			}
			i++;
		}

		return addPacket( packet);
	}
	else
	{
		return TYPE_CONFLICT;
	}
}

np::TransferSuccess np::BufferComponent::addPackets( std::list<np::ResourcePacket*>* packets)
{
	TransferSuccess fResult = TYPE_CONFLICT;

	std::list<np::ResourcePacket*>::iterator i = packets->begin();
	while ( !packets->empty())
	{
		TransferSuccess result = appendPacket( packets->front());

		if ( result == PARTIAL)
		{
			return PARTIAL;
		}
		else if ( result == FULL)
		{
			packets->pop_front();

			fResult = FULL;
		}
		else
		{
			return TYPE_CONFLICT;
		}
	}

	return fResult;
}

double np::BufferComponent::getAmountOf( np::ResourceType* type)
{
	double total = 0.0;
	std::list<np::ResourcePacket*>::iterator i;
	for ( i = buffer.begin(); i != buffer.end(); ++i)
	{
		np::ResourcePacket* packet = *i;
		if ( type == packet->resourceType)
		{
			total += packet->amount;
		}
	}

	return total;
}

np::ResourcePacket* np::BufferComponent::getNextPacketOf( const np::ResourceRequirement* requirements)
{
	std::list<np::ResourcePacket*>::iterator i;
	for ( i = buffer.begin(); i != buffer.end(); ++i)
	{
		np::ResourcePacket* packet = (*i);
		if ( requirements->contains( packet->resourceType))
		{
			buffer.erase( i);
			return packet;
		}
	}

	return NULL;
}

np::ResourcePacket* np::BufferComponent::getPacket( np::ResourceType* type, double amount)
{
	double value = 0.0;

	std::list<np::ResourcePacket*>::iterator i;
	i = buffer.begin();
	while (  i != buffer.end())
	{
		np::ResourcePacket* packet = *i;
		if ( packet->resourceType == type)
		{
			if ( packet->amount <= amount)
			{
				value += packet->amount;
				amount -= packet->amount;

				buffer.erase( i++);
				delete packet;
			}
			else
			{
				packet->amount -= amount;
				value += amount;

				amount = 0.0;

				break;
			}
		}
		else
		{
			i++;
		}
	}

	return new np::ResourcePacket( type, value);
}

np::ResourcePacket* np::BufferComponent::getPacket( np::ResourceType* type)
{
	std::list<np::ResourcePacket*>::iterator i;
	for ( i = buffer.begin(); i != buffer.end(); ++i)
	{
		np::ResourcePacket* packet = (*i);
		if ( packet->resourceType == type)
		{
			buffer.erase( i);
			return packet;
		}
	}

	return NULL;
}

std::list<np::ResourcePacket*> np::BufferComponent::getPackets()
{
	std::list<np::ResourcePacket*> result( buffer);
	buffer.clear();

	return result;
}

std::list<np::ResourcePacket*> np::BufferComponent::getPackets( double amount)
{
	return getPackets( amount, &(np::ResourceRequirement::ANY));
}

std::list<np::ResourcePacket*> np::BufferComponent::getPackets( const np::ResourceRequirement* requirements)
{
	std::list<np::ResourcePacket*> list;

	std::list<np::ResourcePacket*>::iterator i;
	std::list<np::ResourcePacket*>::iterator j;

	np::ResourcePacket* packet;
	np::ResourcePacket* outputPacket;

	for ( i = buffer.begin(); i != buffer.end(); ++i)
	{
		packet = (*i);
		if ( requirements->contains( packet->resourceType))
		{
			bool foundExisting = false;
			for ( j = list.begin(); j != list.end(); ++j)
			{
				outputPacket = (*j);
				if ( outputPacket->resourceType == packet->resourceType)
				{
					foundExisting = true;

					outputPacket->amount += packet->amount;

					buffer.erase( i);
					//delete packet;

					break;
				}
			}

			if ( !foundExisting)
			{
				list.push_back( packet);
			}
		}
	}

	return list;
}

std::list<np::ResourcePacket*> np::BufferComponent::getPackets( double amount, const np::ResourceRequirement* requirements)
{
	//OgreFramework::getSingletonPtr()->m_pLog->logMessage( "BUFFER GET PACKETS REQUEST");
	//OgreFramework::getSingletonPtr()->m_pLog->logMessage( Ogre::StringConverter::toString( (Ogre::Real)amount));

	std::list<np::ResourcePacket*> list;

	std::list<np::ResourcePacket*>::iterator i;
	std::list<np::ResourcePacket*>::iterator j;

	np::ResourcePacket* packet;
	np::ResourcePacket* outputPacket;

	i = buffer.begin();
	while (  i != buffer.end())
	{
		packet = *i;

		if ( requirements->contains( packet->resourceType))
		{
			double pWeight = packet->resourceType->weight();

			bool destroy = packet->amount <= amount / pWeight;
			double pa = std::min( packet->amount, amount / pWeight);

			bool foundExisting = false;
			for ( j = list.begin(); j != list.end(); ++j)
			{
				outputPacket = *j;
				if ( outputPacket->resourceType == packet->resourceType)
				{
					foundExisting = true;

					outputPacket->amount += pa;
					packet->amount -= pa;

					if ( destroy)
					{
						buffer.erase( i++);
						delete packet;
					}

					break;
				}
			}

			if ( !foundExisting)
			{
				np::ResourcePacket* newPacket;

				if ( destroy)
				{
					buffer.erase( i++);
					newPacket = packet;
				}
				else
				{
					packet->amount -= pa;
					newPacket = new np::ResourcePacket( packet->resourceType, pa);
				}

				//OgreFramework::getSingletonPtr()->m_pLog->logMessage( Ogre::StringConverter::toString( (Ogre::Real)newPacket->amount));
				list.push_back( newPacket);
			}

			amount -= pa * pWeight;

			if ( !destroy) break;
		}
		else
		{
			++i;
		}
	}

	return list;
}

bool np::BufferComponent::isEmpty()
{
	return buffer.empty();
}

void np::BufferComponent::clear()
{
	std::list<np::ResourcePacket*>::iterator i;
	for ( i = buffer.begin(); i != buffer.end(); ++i)
	{
		delete (*i);
	}
	buffer.clear();
}
