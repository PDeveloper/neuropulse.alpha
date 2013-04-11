#include <ac/es.h>

#pragma once
namespace np
{
	class ConstructConnectionSystem : public ac::es::EntityProcessingSystem
	{
		AC_ES_ENTITY_SYSTEM(ConstructConnectionSystem)
	public:
		ConstructConnectionSystem(void);
		~ConstructConnectionSystem(void);
	protected:
		void process( ac::es::EntityPtr e);
	};
}
