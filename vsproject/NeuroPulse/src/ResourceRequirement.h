#include <string>
#include <limits>

#include <ResourceType.h>

#pragma once
#include "BitFlag.h"
namespace np
{

	class ResourceRequirement
	{
	public:

		static const np::ResourceRequirement ANY;

		np::BitFlag bits;

		unsigned long int getFlag() const;

		np::ResourceRequirement& set( unsigned long int flag);

		np::ResourceRequirement& add( np::ResourceType* type);
		np::ResourceRequirement& add( np::ResourceRequirement* requirement);

		np::ResourceRequirement& remove( np::ResourceType* type);
		np::ResourceRequirement& remove( np::ResourceRequirement* requirement);

		bool contains( np::ResourceType* type) const;
		bool contains( np::ResourceRequirement* requirement) const;

		ResourceRequirement( np::ResourceType* type);
		ResourceRequirement( const np::BitFlag& bits);
		ResourceRequirement( unsigned long int flag = 0);

		bool operator==( const ResourceRequirement& other) const
		{
			return bits == other.bits;
		}

		bool operator==( const ResourceType& other) const
		{
			return bits == other.bits;
		}

		bool operator < ( const ResourceRequirement& other) const
		{
			return bits < other.bits;
		}

		bool operator > ( const ResourceRequirement& other) const
		{
			return bits > other.bits;
		}

		bool operator > ( const ResourceType& other) const
		{
			return bits > other.bits;
		}

		ResourceRequirement& operator += (ResourceRequirement& other)
		{
			bits += other.bits;

			return *this;
		}

		ResourceRequirement operator + (ResourceRequirement& other)
		{
			return ResourceRequirement( other.bits + bits);
		}

		ResourceRequirement& operator += (ResourceType& other)
		{
			bits += other.bits;

			return *this;
		}

		ResourceRequirement operator + (ResourceType& other)
		{
			return ResourceRequirement( other.bits + bits);
		}

		ResourceRequirement& operator -= (ResourceRequirement& other)
		{
			bits -= other.bits;

			return *this;
		}

		ResourceRequirement operator - (ResourceType& other)
		{
			return ResourceRequirement( other.bits - bits);
		}

		ResourceRequirement& operator -= (ResourceType& other)
		{
			bits -= other.bits;

			return *this;
		}

		ResourceRequirement operator - (ResourceRequirement& other)
		{
			return ResourceRequirement( other.bits - bits);
		}

	private:
		unsigned long int flag;
	};
}