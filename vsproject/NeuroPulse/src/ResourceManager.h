#include <string>
#include <vector>

#include <ResourceRequirement.h>

#include <ResourceType.h>
#include <OgreSingleton.h>

#pragma once
namespace np
{

	class ResourceManager : public Ogre::Singleton<np::ResourceManager>
	{
	public:
		bool registerType( std::string name, std::string description, double weight);

		np::ResourceType* getType( std::string name);
		np::ResourceRequirement* getReq( std::string names[], size_t numNames);

		std::vector<np::ResourceType*> getTypes(np::ResourceRequirement* req);

		ResourceManager(void);
		~ResourceManager(void);
	private:
		std::vector<np::ResourceType> resourceTypes;

		ResourceManager(const ResourceManager&);
		ResourceManager& operator= (const ResourceManager&);
	};

}