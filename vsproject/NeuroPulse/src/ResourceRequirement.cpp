#include "ResourceRequirement.h"

const np::ResourceRequirement np::ResourceRequirement::ANY = np::ResourceRequirement(std::numeric_limits<unsigned long>::max());

np::ResourceRequirement::ResourceRequirement( np::ResourceType* type)
{
	this->flag = type->getFlag();
}

np::ResourceRequirement::ResourceRequirement( unsigned long int flag)
{
	this->flag = flag;
}

unsigned long int np::ResourceRequirement::getFlag() const
{
	return flag;
}

np::ResourceRequirement& np::ResourceRequirement::set( unsigned long int flag)
{
	this->flag = flag;

	return *this;
}

np::ResourceRequirement& np::ResourceRequirement::add( np::ResourceType* type)
{
	flag = type->getFlag() | flag;

	return *this;
}

np::ResourceRequirement& np::ResourceRequirement::add( np::ResourceRequirement* requirement)
{
	flag = requirement->getFlag() | flag;

	return *this;
}

np::ResourceRequirement& np::ResourceRequirement::remove( np::ResourceType* type)
{
	flag = !type->getFlag() & flag;

	return *this;
}

np::ResourceRequirement& np::ResourceRequirement::remove( np::ResourceRequirement* requirement)
{
	flag = !requirement->getFlag() & flag;

	return *this;
}

bool np::ResourceRequirement::contains( np::ResourceType* type) const
{
	return ( type->getFlag() & flag) == type->getFlag();
}

bool np::ResourceRequirement::contains( np::ResourceRequirement* requirement) const
{
	return ( requirement->getFlag() & flag) == requirement->getFlag();
}