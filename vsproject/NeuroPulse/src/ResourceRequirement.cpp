#include "ResourceRequirement.h"

const np::ResourceRequirement np::ResourceRequirement::ANY = np::ResourceRequirement( (const np::BitFlag&) np::BitFlag::ALL);

np::ResourceRequirement::ResourceRequirement( np::ResourceType* type) :
	bits( type->bits)
{
	this->flag = type->getFlag();
}

np::ResourceRequirement::ResourceRequirement( unsigned long int flag) :
	bits( flag)
{
	this->flag = flag;
}

np::ResourceRequirement::ResourceRequirement( const np::BitFlag& bits) :
	bits( bits)
{
	this->flag = 0;
}

unsigned long int np::ResourceRequirement::getFlag() const
{
	return flag;
}

np::ResourceRequirement& np::ResourceRequirement::set( unsigned long int flag)
{
	bits.setBits( flag);
	this->flag = flag;

	return *this;
}

np::ResourceRequirement& np::ResourceRequirement::add( np::ResourceType* type)
{
	bits += type->bits;
	flag = type->getFlag() | flag;

	return *this;
}

np::ResourceRequirement& np::ResourceRequirement::add( np::ResourceRequirement* requirement)
{
	bits += requirement->bits;
	flag = requirement->getFlag() | flag;

	return *this;
}

np::ResourceRequirement& np::ResourceRequirement::remove( np::ResourceType* type)
{
	bits -= type->bits;
	flag = !type->getFlag() & flag;

	return *this;
}

np::ResourceRequirement& np::ResourceRequirement::remove( np::ResourceRequirement* requirement)
{
	bits -= requirement->bits;
	flag = !requirement->getFlag() & flag;

	return *this;
}

bool np::ResourceRequirement::contains( np::ResourceType* type) const
{
	return type->bits < bits;
	return ( type->getFlag() & flag) == type->getFlag();
}

bool np::ResourceRequirement::contains( np::ResourceRequirement* requirement) const
{
	return requirement->bits < bits;
	return ( requirement->getFlag() & flag) == requirement->getFlag();
}