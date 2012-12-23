#include "AdvancedOgreFramework.hpp"
#include "AppStateManager.hpp"

#pragma once
class ApplicationBase
{
private:
	AppStateManager*	m_pAppStateManager;
public:
	ApplicationBase(void);
	~ApplicationBase(void);
	bool run(void);
};

