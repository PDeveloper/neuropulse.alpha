#include <OgreRoot.h>

#pragma once
class OgreManager
{
private:
	Ogre::Root* mRoot;
    Ogre::String mPluginsCfg;
	Ogre::String mResourcesCfg;

	Ogre::RenderWindow* mWindow;
public:
	OgreManager(void);
	~OgreManager(void);
	bool init(void);
};

