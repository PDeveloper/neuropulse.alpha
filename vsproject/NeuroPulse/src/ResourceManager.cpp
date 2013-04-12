#include "ResourceManager.h"

template<> np::ResourceManager* Ogre::Singleton<np::ResourceManager>::msSingleton = 0;

np::ResourceManager::ResourceManager(void) :
	resourceTypes()
{
}

np::ResourceManager::~ResourceManager(void)
{

}

bool np::ResourceManager::registerType( std::string name, std::string description, Ogre::ColourValue colour)
{
	std::vector<np::ResourceType>::iterator i;

	for( i = resourceTypes.begin(); i != resourceTypes.end(); ++i)
		if ( (*i).name() == name)
		{
			return false;
		}

	resourceTypes.push_back( np::ResourceType( name, description, colour, resourceTypes.size()));

	return true;
}

np::ResourceType* np::ResourceManager::getType( std::string name)
{
	std::vector<np::ResourceType>::iterator i;

	for( i = resourceTypes.begin(); i != resourceTypes.end(); ++i)
		if ( (*i).name() == name)
		{
			return &(*i);
		}

	return NULL;
}

np::ResourceRequirement* np::ResourceManager::getReq( std::string names[], size_t numNames )
{
	np::ResourceRequirement* req = new np::ResourceRequirement();

	for ( size_t i = 0; i < numNames; i++)
	{
		req->add( getType( names[i]));
	}

	return req;
}

std::vector<np::ResourceType*> np::ResourceManager::getTypes( np::ResourceRequirement* req)
{
	std::vector<np::ResourceType*> types;

	for(int i=0; i<resourceTypes.size(); i++)
	{
		if(req->contains(&resourceTypes.at(i)))
		{
			types.push_back(&resourceTypes.at(i));
		}
	}

	return types;
}
