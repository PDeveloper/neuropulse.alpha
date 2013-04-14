#pragma once
#include <ac/es.h>
namespace np
{

	class NeuroWorld;

	class CameraControlSystem : public ac::es::EntityProcessingSystem
	{
		AC_ES_ENTITY_SYSTEM(CameraControlSystem)
	public:

		np::NeuroWorld* world;

		CameraControlSystem( np::NeuroWorld* world);
		~CameraControlSystem(void);

	protected:
		virtual void process( ac::es::EntityPtr e);
	};
}
