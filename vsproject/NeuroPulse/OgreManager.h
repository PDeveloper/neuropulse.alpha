#include <OgreRoot.h>

#pragma once
class OgreManager
{
private:
	Ogre::Root* mRoot;
    Ogre::String mPluginsCfg;
public:
	OgreManager(void);
	~OgreManager(void);
	bool init(void);
};

