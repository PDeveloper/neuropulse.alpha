#include <string>
#include <vector>

#include <ResourceType.h>
#include <OgreSingleton.h>

#pragma once
namespace np
{

	class ResourceManager : public Ogre::Singleton<np::ResourceManager>
	{
	public:
		bool registerType( std::string name, std::string description);
		np::ResourceType* getType( std::string name);

		ResourceManager(void);
		~ResourceManager(void);
	private:
		std::vector<np::ResourceType> resourceTypes;

		ResourceManager(const ResourceManager&);
		ResourceManager& operator= (const ResourceManager&);
	};

}