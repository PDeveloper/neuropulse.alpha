#include <ac\es.h>
#include <OgreSceneManager.h>

#pragma once
class GraphicSystem : public ac::es::EntityProcessingSystem
{
	AC_ES_ENTITY_SYSTEM(GraphicSystem)
public:
	GraphicSystem(void);
	~GraphicSystem(void);
protected:
	virtual void process( ac::es::Entity& e);
};

