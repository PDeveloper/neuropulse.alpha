#include "HeatSystem.h"

#include "HubComponent.h"
#include "BufferComponent.h"
#include "NodeComponent.h"

#include <ResourcePacket.h>

#include <AdvancedOgreFramework.hpp>


np::HeatSystem::HeatSystem(GameObjectFactory* gameObjectFactory) :
	ac::es::EntityProcessingSystem( ac::es::ComponentFilter::Requires<NodeComponent>().requires<BufferComponent>())
{
	deltaTime = 0.0;
	heat = np::ResourceManager::getSingletonPtr()->getType( "Heat");
	requirement = new np::ResourceRequirement( heat);

	this->gameObjectFactory = gameObjectFactory;
}


np::HeatSystem::~HeatSystem(void)
{
}

void np::HeatSystem::setDeltaTime( double time)
{
	deltaTime = time;
}

void np::HeatSystem::process( ac::es::EntityPtr e)
{
	np::BufferComponent* buffer = e->getComponent<BufferComponent>();
	np::NodeComponent* node = e->getComponent<NodeComponent>();
	np::HubComponent* hub = e->getComponent<HubComponent>();

	

	//OgreFramework::getSingletonPtr()->m_pLog->logMessage("BingBong");
	//Dissipate heat to environment
	buffer->getPackets( (node->temperature) * node->heatDissipation * ( deltaTime / 1000.0), requirement);

	//Calculate temperature
	node->temperature = buffer->getAmountOf(heat) / node->heatCapacity;

	//Deal with hub
	if(hub != NULL)
	{
		//Overheating
		if(node->temperature > hub->overheatTemperature)
		{
			double damage = (node->temperature - hub->overheatTemperature) * hub->overheatDamage * ( deltaTime / 1000.0);
			hub->health -= damage;

			//Kill?
			if(hub->health <= 0)
			{
				hub->destroy();
				gameObjectFactory->killHub(e);
			}
		}
	}
	
	

	

	
	

	

	//// DEBUGGING ONLY!!!!!
	//np::TransformComponent* transform = e->getComponent<np::TransformComponent>();
	//transform->position.y = node->currentEnergy * 0.5;
	////
}