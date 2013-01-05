#include <ac\es.h>

#pragma once
namespace np
{
	class ReactionSystem : public ac::es::EntityProcessingSystem
	{
		AC_ES_ENTITY_SYSTEM(ReactionSystem)
	public:
		ReactionSystem(void);
		~ReactionSystem(void);

	protected:
		virtual void process( ac::es::EntityPtr e);
	};
}