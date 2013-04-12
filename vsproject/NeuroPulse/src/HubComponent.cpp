#include <HubComponent.h>
#include <ConstructComponent.h>
#include "GraphicComponent.h"

np::HubComponent::HubComponent( np::NeuroPlayer* owner)
{
	this->owner = owner;

	health = 100.0;
	
	overheatTemperature = 3500;
	overheatDamage = 0.05;

	_isShown = true;
}

np::HubComponent::~HubComponent(void)
{

}

void np::HubComponent::destroy()
{
	//Explode or some fancy shit like that
}

void np::HubComponent::showStructures()
{
	if ( !_isShown)
	{
		_isShown = true;

		std::list<ac::es::EntityPtr>::iterator iterator;
		ac::es::EntityPtr e;

		for ( iterator = constructs.begin(); iterator != constructs.end(); ++iterator)
		{
			e = (*iterator);
			np::GraphicComponent* graphic = e->getComponent<np::GraphicComponent>();

			graphic->show();
		}
		for ( iterator = buds.begin(); iterator != buds.end(); ++iterator)
		{
			e = (*iterator);
			np::GraphicComponent* graphic = e->getComponent<np::GraphicComponent>();

			graphic->show();
		}
		for ( iterator = gates.begin(); iterator != gates.end(); ++iterator)
		{
			e = (*iterator);
			np::GraphicComponent* graphic = e->getComponent<np::GraphicComponent>();

			graphic->show();
		}
		for ( iterator = connections.begin(); iterator != connections.end(); ++iterator)
		{
			e = (*iterator);
			np::GraphicComponent* graphic = e->getComponent<np::GraphicComponent>();

			graphic->show();
		}
	}
}

void np::HubComponent::hideStructures()
{
	if ( _isShown)
	{
		_isShown = false;

		std::list<ac::es::EntityPtr>::iterator iterator;
		ac::es::EntityPtr e;

		for ( iterator = constructs.begin(); iterator != constructs.end(); ++iterator)
		{
			e = (*iterator);
			np::GraphicComponent* graphic = e->getComponent<np::GraphicComponent>();

			graphic->hide();
		}
		for ( iterator = buds.begin(); iterator != buds.end(); ++iterator)
		{
			e = (*iterator);
			np::GraphicComponent* graphic = e->getComponent<np::GraphicComponent>();

			graphic->hide();
		}
		for ( iterator = gates.begin(); iterator != gates.end(); ++iterator)
		{
			e = (*iterator);
			np::GraphicComponent* graphic = e->getComponent<np::GraphicComponent>();

			graphic->hide();
		}
		for ( iterator = connections.begin(); iterator != connections.end(); ++iterator)
		{
			e = (*iterator);
			np::GraphicComponent* graphic = e->getComponent<np::GraphicComponent>();

			graphic->hide();
		}
	}
}

void np::HubComponent::addConstruct( ac::es::EntityPtr e )
{
	constructs.push_back( e);

	initVisual( e);
}

void np::HubComponent::removeConstruct( ac::es::EntityPtr e )
{
	constructs.remove( e);
}

void np::HubComponent::addBud( ac::es::EntityPtr e )
{
	buds.push_back( e);

	initVisual( e);
}

void np::HubComponent::removeBud( ac::es::EntityPtr e )
{
	buds.remove( e);
}

void np::HubComponent::addGate( ac::es::EntityPtr e )
{
	gates.push_back( e);

	initVisual( e);
}

void np::HubComponent::removeGate( ac::es::EntityPtr e )
{
	gates.remove( e);
}

void np::HubComponent::addConnection( ac::es::EntityPtr e )
{
	connections.push_back( e);

	initVisual( e);
}

void np::HubComponent::removeConnection( ac::es::EntityPtr e )
{
	connections.remove( e);
}

void np::HubComponent::initVisual( ac::es::EntityPtr e )
{
	np::GraphicComponent* graphic = e->getComponent<np::GraphicComponent>();

	if ( _isShown) graphic->show();
	else graphic->hide();
}

ac::es::EntityPtr np::HubComponent::getConstruct( int slot )
{
	std::list<ac::es::EntityPtr>::iterator iterator = constructs.begin();
	for ( int i = 0; i < slot; i++) iterator++;
	return *iterator;
}
