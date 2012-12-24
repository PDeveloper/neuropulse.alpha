#include <ac\es.h>

#pragma once
class EntityFactory
{
public:
	EntityFactory(void);
	~EntityFactory(void);

	void createNodeEntity( ac::es::EntityPtr);
};

