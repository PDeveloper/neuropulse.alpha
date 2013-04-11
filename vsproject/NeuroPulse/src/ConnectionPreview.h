#include <ac/es.h>
#include <OgreVector3.h>
#include <OgreColourValue.h>

#pragma once
namespace np
{
	class ConnectionPreview
	{
	public:

		void show();
		void hide();

		void updateSource( const Ogre::Vector3& source);
		void updateTarget( const Ogre::Vector3& target);

		void setColor( Ogre::ColourValue& colour);

		ConnectionPreview( ac::es::EntityPtr constructConnectionEntity);
		~ConnectionPreview(void);
	private:

		bool _isShowing;

		const Ogre::Vector3* target;

		ac::es::EntityPtr previewConnection;
	};
}
