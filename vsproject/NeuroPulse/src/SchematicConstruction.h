#pragma once
#include <Construct.h>

namespace np
{
	class SchematicConstruction : public Construct
	{
	public:

		void process();
		void processInstructions(np::ResourcePacket* packet);

		np::Construct* getUpgrade();

		std::string getName();
		std::string getDescription();

		double takeEnergy;
		double conversionRate;

		SchematicConstruction(void);
		~SchematicConstruction(void);
	private:
		np::ResourceType* sexyEnergy;

		bool constructionCompleted;
		double constructionProgress;
	};
}
