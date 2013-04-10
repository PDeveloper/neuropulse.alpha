#include <ConstructConnectionComponent.h>

np::ConstructConnectionComponent::ConstructConnectionComponent( ac::es::EntityPtr entity1, ac::es::EntityPtr entity2)
{
	this->entity1 = entity1;
	this->entity2 = entity2;

	this->target1 = entity1->getComponent<np::TransformComponent>();
	this->target2 = entity2->getComponent<np::TransformComponent>();
}

np::ConstructConnectionComponent::~ConstructConnectionComponent(void)
{
}
