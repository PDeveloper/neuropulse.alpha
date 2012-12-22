#include "OgreManager.h"

OgreManager::OgreManager(void):
	mRoot(0),
    mPluginsCfg(Ogre::StringUtil::BLANK)
{
}


OgreManager::~OgreManager(void)
{
	delete mRoot;
}

bool OgreManager::init(void)
{
#ifdef _DEBUG
    mPluginsCfg = "plugins_d.cfg";
#else
    mPluginsCfg = "plugins.cfg";
#endif
	
    // construct Ogre::Root
    mRoot = new Ogre::Root( mPluginsCfg);
	
    return true;
}