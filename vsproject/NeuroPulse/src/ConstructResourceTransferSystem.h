#include <ac\es.h>

#pragma once
namespace np
{
	class ConstructResourceTransferSystem : public ac::es::EntityProcessingSystem
	{
		AC_ES_ENTITY_SYSTEM(ConstructResourceTransferSystem)
	public:
		ConstructResourceTransferSystem();
		~ConstructResourceTransferSystem(void);


	protected:
		void onBeginProcessing();
		void process( ac::es::EntityPtr e);
		void onEndProcessing();

	};
}