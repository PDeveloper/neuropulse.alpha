#include <ac\es.h>
#include <ResourceManager.h>
#include <GameObjectFactory.h>

#pragma once
namespace np
{
	class HeatSystem : public ac::es::EntityProcessingSystem
	{
		AC_ES_ENTITY_SYSTEM(HeatSystem)
	public:

		HeatSystem(GameObjectFactory* gameObjectFactory);
		~HeatSystem(void);

		void setDeltaTime( double time);

	protected:
		virtual void process( ac::es::EntityPtr e);

	private:
		double deltaTime;
		np::ResourceRequirement* requirement;
		np::ResourceType* heat;

		GameObjectFactory* gameObjectFactory;
	};
}