#include <ac\es.h>

#pragma once
namespace np
{
	class ConstructSystem : public ac::es::EntityProcessingSystem
	{
		AC_ES_ENTITY_SYSTEM(ConstructSystem)
	public:

		

		ConstructSystem();
		~ConstructSystem(void);

		
	protected:
		void process( ac::es::EntityPtr e);
	
	};
}