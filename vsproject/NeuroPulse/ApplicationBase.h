#include "OgreManager.h"

#pragma once
class ApplicationBase
{
private:
	OgreManager* manager;
public:
	ApplicationBase(void);
	~ApplicationBase(void);
	bool run(void);
};

