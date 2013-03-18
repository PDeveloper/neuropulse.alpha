#include <ac\es.h>
#include <ResourceManager.h>

#pragma once
namespace np
{
	class ReactionSystem : public ac::es::EntityProcessingSystem
	{
		AC_ES_ENTITY_SYSTEM(ReactionSystem)
	public:
		ReactionSystem(void);
		~ReactionSystem(void);

		void setDeltaTime( double time);

	protected:
		virtual void process( ac::es::EntityPtr e);

	private:
		double deltaTime;
		np::ResourceType* rawEnergy;
	};
}