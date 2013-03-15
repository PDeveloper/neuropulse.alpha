#include <ac\es.h>

#pragma once
namespace np
{
	class ConstructConnectionSystem : public ac::es::EntityProcessingSystem
	{
		AC_ES_ENTITY_SYSTEM(ConstructConnectionSystem)
	public:



		ConstructConnectionSystem();
		~ConstructConnectionSystem(void);


	protected:
		void onBeginProcessing();
		void process( ac::es::EntityPtr e);
		void onEndProcessing();

	};
}