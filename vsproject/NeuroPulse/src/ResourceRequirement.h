#include <string>
#include <limits>

#include <ResourceType.h>

#pragma once
namespace np
{

	class ResourceRequirement
	{
	public:

		static const np::ResourceRequirement ANY;

		unsigned long int getFlag() const;

		np::ResourceRequirement& set( unsigned long int flag);

		np::ResourceRequirement& add( np::ResourceType* type);
		np::ResourceRequirement& add( np::ResourceRequirement* requirement);

		np::ResourceRequirement& remove( np::ResourceType* type);
		np::ResourceRequirement& remove( np::ResourceRequirement* requirement);

		bool contains( np::ResourceType* type) const;
		bool contains( np::ResourceRequirement* requirement) const;

		bool operator==(ResourceRequirement& other) const
		{
			return flag == other.getFlag();
		}

		ResourceRequirement( np::ResourceType* type);
		ResourceRequirement( unsigned long int flag = 0);

	private:
		unsigned long int flag;
	};
}