#include <ac\es.h>

#include <EventManager.h>

#include <GameObjectFactory.h>

#include <ResourceRequirement.h>

#pragma once
namespace np
{

	class PulseTransferSystem : public ac::es::EntityProcessingSystem
	{
		AC_ES_ENTITY_SYSTEM(PulseTransferSystem)
	public:

		np::ResourceRequirement* requirement;
		np::ResourceType* rawEnergy;

		PulseTransferSystem(void);
		~PulseTransferSystem(void);
		void process( ac::es::EntityPtr e);
	};

}