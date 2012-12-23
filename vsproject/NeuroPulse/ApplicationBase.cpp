#include "ApplicationBase.h"

ApplicationBase::ApplicationBase(void)
{
	manager = new OgreManager();
}


ApplicationBase::~ApplicationBase(void)
{
}

bool ApplicationBase::run(void)
{
	bool success = manager->init();

	return success;
}