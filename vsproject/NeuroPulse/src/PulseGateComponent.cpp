#include "PulseGateComponent.h"
#include <hash_map>
#include "ListProperty.h"


np::PulseGateComponent::PulseGateComponent( int connection, double position, ac::es::EntityPtr nodeEntity)
{
	this->connectionIndex = connection;
	this->position = position;
	this->nodeEntity = nodeEntity;

	componentInterface = new np::ComponentInterface();
	
	std::hash_map<std::string, int>* modeMap = new std::hash_map<std::string, int>();
	(*modeMap)["All"] = MODE_ALL;
	(*modeMap)["Incoming"] = MODE_INCOMING;
	(*modeMap)["Outgoing"] = MODE_OUTGOING;
	(*modeMap)["None"] = MODE_NONE;
	mode = MODE_OUTGOING;

	componentInterface->addProperty(new ListProperty("PulseGate", "Mode", &mode,  modeMap));
	
}


np::PulseGateComponent::~PulseGateComponent(void)
{
}
