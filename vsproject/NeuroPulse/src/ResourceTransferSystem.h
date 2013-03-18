#include <ac\es.h>

#pragma once
namespace np
{
	class ResourceTransferSystem : public ac::es::EntityProcessingSystem
	{
		AC_ES_ENTITY_SYSTEM(ResourceTransferSystem)
	public:
		ResourceTransferSystem();
		~ResourceTransferSystem(void);


	protected:
		void process( ac::es::EntityPtr e);

	};
}