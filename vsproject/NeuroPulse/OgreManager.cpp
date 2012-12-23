#include "OgreManager.h"
#include <OgreConfigFile.h>

OgreManager::OgreManager(void):
	mRoot(0),
	mResourcesCfg(Ogre::StringUtil::BLANK),
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
    mResourcesCfg = "ogre/resources_d.cfg";
    mPluginsCfg = "ogre/plugins_d.cfg";
#else
    mResourcesCfg = "ogre/resources.cfg";
    mPluginsCfg = "ogre/plugins.cfg";
#endif
	
    // construct Ogre::Root
    mRoot = new Ogre::Root( mPluginsCfg);

	// set up resources
	// Load resource paths from config file
	Ogre::ConfigFile cf;
	cf.load(mResourcesCfg);

	// Go through all sections & settings in the file
	Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
	
	Ogre::String secName, typeName, archName;
	while ( seci.hasMoreElements())
	{
		secName = seci.peekNextKey();

		Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator i;

		for (i = settings->begin(); i != settings->end(); ++i)
		{
			typeName = i->first;
			archName = i->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation( archName, typeName, secName);
		}
	}

	// configure
	// Show the configuration dialog and initialise the system
	if( !(/*mRoot->restoreConfig() || */mRoot->showConfigDialog()))
	{
		return false;
	}

	mWindow = mRoot->initialise( true, "Ogre3d Window");

	// Set default mipmap level (note: some APIs ignore this)
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	// initialise all resource groups
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

    return true;
}