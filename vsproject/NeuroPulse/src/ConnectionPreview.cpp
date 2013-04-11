#include "ConnectionPreview.h"
#include <GraphicComponent.h>
#include <TransformComponent.h>

np::ConnectionPreview::ConnectionPreview( ac::es::EntityPtr constructConnectionEntity)
{
	this->previewConnection = constructConnectionEntity;
	np::TransformComponent* transform = previewConnection->getComponent<np::TransformComponent>();
	
	updateTarget( transform->rotation.zAxis());
	_isShowing = true;
}

np::ConnectionPreview::~ConnectionPreview(void)
{
}

void np::ConnectionPreview::show()
{
	if ( !_isShowing)
	{
		_isShowing = true;

		np::GraphicComponent* graphic = previewConnection->getComponent<np::GraphicComponent>();
		graphic->show();
	}
}

void np::ConnectionPreview::hide()
{
	if ( _isShowing)
	{
		_isShowing = false;

		np::GraphicComponent* graphic = previewConnection->getComponent<np::GraphicComponent>();
		graphic->hide();
	}
}

void np::ConnectionPreview::updateSource( const Ogre::Vector3& source )
{
	np::TransformComponent* transform = previewConnection->getComponent<np::TransformComponent>();

	transform->position = source;
}

void np::ConnectionPreview::updateTarget( const Ogre::Vector3& target )
{
	this->target = &target;

	np::TransformComponent* transform = previewConnection->getComponent<np::TransformComponent>();

	double distance = transform->position.distance( target);
	double d = distance / 100.0;

	transform->rotation = Ogre::Vector3::UNIT_Z.getRotationTo( target - transform->position);
	transform->scale = Ogre::Vector3( 1.0, 1.0, d);
}

void np::ConnectionPreview::setColor( Ogre::ColourValue& colour )
{
	np::GraphicComponent* graphic = previewConnection->getComponent<np::GraphicComponent>();

	std::list<Ogre::Entity*>::iterator iterator;
	for ( iterator = graphic->entities.begin(); iterator != graphic->entities.end(); ++iterator)
	{
		(*iterator)->getSubEntity(0)->getMaterial()->setDiffuse( colour);
	}
}
