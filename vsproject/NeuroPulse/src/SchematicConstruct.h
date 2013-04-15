#pragma once
#include <Construct.h>

namespace np
{
	class SchematicConstruct : public Construct
	{
	public:

		void process(float timeSinceLastUpdate);
		void processInstructions(np::ResourcePacket* packet);

		np::Construct* getUpgrade()
		{
			return NULL;
		}

		std::string getName();
		std::string getDescription();

		SchematicConstruct(void);
		~SchematicConstruct(void);

		np::Construct* getNewInstance()
		{
			return new np::SchematicConstruct();
		}
	private:
		np::ResourceType* sexyEnergy;
		np::ResourceType* hubSchematics;

		double currentHubSchematicProgress;
	};
}
