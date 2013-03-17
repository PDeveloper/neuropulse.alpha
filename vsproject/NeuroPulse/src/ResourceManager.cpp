#include "ResourceManager.h"


template<> np::ResourceManager* Ogre::Singleton<np::ResourceManager>::msSingleton = 0;

np::ResourceManager::ResourceManager(void) :
	resourceTypes()
{
}

np::ResourceManager::~ResourceManager(void)
{

}

bool np::ResourceManager::registerType( std::string name, std::string description )
{
	std::vector<np::ResourceType>::iterator i;

	for( i = resourceTypes.begin(); i != resourceTypes.end(); ++i)
		if ( (*i).name() == name)
		{
			return false;
		}

	resourceTypes.push_back( np::ResourceType( name, description, resourceTypes.size()));

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
