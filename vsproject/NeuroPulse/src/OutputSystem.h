#include <ac\es.h>

#pragma once
namespace np
{
	class OutputSystem : public ac::es::EntityProcessingSystem
	{
		AC_ES_ENTITY_SYSTEM(OutputSystem)
	public:
		OutputSystem(void);
		~OutputSystem(void);

	protected:
		virtual void process( ac::es::EntityPtr e);
	};
}