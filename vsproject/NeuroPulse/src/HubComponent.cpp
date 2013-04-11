#include <HubComponent.h>
#include <ConstructComponent.h>
#include "GraphicComponent.h"

np::HubComponent::HubComponent( np::NeuroPlayer* owner) :
	constructs()
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

		std::vector<ac::es::EntityPtr>::iterator iterator;
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

		std::vector<ac::es::EntityPtr>::iterator iterator;
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
	for ( std::vector<ac::es::EntityPtr>::iterator iterator = constructs.begin(); iterator != constructs.end(); ++iterator)
	{
		if ( (*iterator) == e) constructs.erase( iterator);
	}
}

void np::HubComponent::addBud( ac::es::EntityPtr e )
{
	buds.push_back( e);

	initVisual( e);
}

void np::HubComponent::removeBud( ac::es::EntityPtr e )
{
	for ( std::vector<ac::es::EntityPtr>::iterator iterator = buds.begin(); iterator != buds.end(); ++iterator)
	{
		if ( (*iterator) == e) buds.erase( iterator);
	}
}

void np::HubComponent::addConnection( ac::es::EntityPtr e )
{
	connections.push_back( e);

	initVisual( e);
}

void np::HubComponent::removeConnection( ac::es::EntityPtr e )
{
	for ( std::vector<ac::es::EntityPtr>::iterator iterator = connections.begin(); iterator != connections.end(); ++iterator)
	{
		if ( (*iterator) == e) connections.erase( iterator);
	}
}

void np::HubComponent::initVisual( ac::es::EntityPtr e )
{
	np::GraphicComponent* graphic = e->getComponent<np::GraphicComponent>();

	if ( _isShown) graphic->show();
	else graphic->hide();
}
