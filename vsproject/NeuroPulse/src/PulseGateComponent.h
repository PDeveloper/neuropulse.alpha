#include <ac/es.h>
#include <ComponentInterface.h>




#pragma once
namespace np
{

	class PulseGateComponent : public ac::es::Component
	{
		AC_ES_COMPONENT(PulseGateComponent)
	public:
		enum Mode
		{
			MODE_ALL = 0,
			MODE_INCOMING = 1,
			MODE_OUTGOING = 2,
			MODE_NONE = 3
		}; 

		double position;
		int connectionIndex;
		ac::es::EntityPtr nodeEntity;

		np::ComponentInterface* componentInterface;
		
		int mode;

		PulseGateComponent( int connectionIndex, double position, ac::es::EntityPtr nodeEntity);
		~PulseGateComponent(void);
	};

}