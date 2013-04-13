#pragma once
#include <ac/es.h>

#include <ResourceRequirement.h>

namespace np
{

	class NeuroWorld;

	class HubConstructionSystem : public ac::es::EntityProcessingSystem
	{
		AC_ES_ENTITY_SYSTEM(HubConstructionSystem)
	public:

		np::NeuroWorld* world;

		np::ResourceRequirement hubSchematicRequirement;

		HubConstructionSystem(np::NeuroWorld* world);
		~HubConstructionSystem(void);

	protected:
		virtual void process( ac::es::EntityPtr e);
	};
}
