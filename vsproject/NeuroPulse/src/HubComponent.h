#include <ac\es.h>
#include <vector>
#include <list>

#include <NeuroPlayer.h>
#include <OgreEntity.h>

/**
	HubComponent
	Manages constructs
**/

#pragma once
namespace np
{

	
	class HubComponent : public ac::es::Component
	{
		AC_ES_COMPONENT(HubComponent)
	public:

		np::NeuroPlayer* owner;
		std::list<ac::es::EntityPtr> constructs;
		std::list<ac::es::EntityPtr> buds;
		std::list<ac::es::EntityPtr> gates;
		std::list<ac::es::EntityPtr> connections;

		Ogre::Entity* display;

		//Heat stuff
		double health;
		
		double overheatTemperature;
		double overheatDamage;

		void addConstruct( ac::es::EntityPtr construct);
		void removeConstruct( ac::es::EntityPtr construct);

		void addBud( ac::es::EntityPtr bud);
		void removeBud( ac::es::EntityPtr bud);

		void addGate( ac::es::EntityPtr gate);
		void removeGate( ac::es::EntityPtr gate);

		void addConnection( ac::es::EntityPtr connection);
		void removeConnection( ac::es::EntityPtr connection);

		ac::es::EntityPtr getConstruct( int slot);
		
		void showStructures();
		void hideStructures();

		HubComponent( np::NeuroPlayer* owner);
		~HubComponent(void);

		void destroy();
	private:
		bool _isShown;

		void initVisual( ac::es::EntityPtr e);
	};
}