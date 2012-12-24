///
/// AES - Anax Entity System
/// Copyright (C) 2012 Anax Creations. All rights reserved.
///
///
/// This software is provided 'as-is', without any express or implied warranty.
/// In no event will the authors be held liable for any damages arising from the
/// use of this software.
///
/// Permission is hereby granted, free of charge, to any person
/// obtaining a copy of this software and associated documentation files (the "Software"),
/// to deal in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions:
///
/// 1. The origin of this software must not be misrepresented;
///    you must not claim that you wrote the original software.
///    If you use this software in a product, an acknowledgment
///    in the product documentation would be appreciated but is not required.
///
/// 2. Altered source versions must be plainly marked as such,
///	   and must not be misrepresented as being the original software.
///
/// 3. The above copyright notice and this permission notice shall be included in
///    all copies or substantial portions of the Software.
///

#ifndef __AC_ES_ENTITYOBSERVER_H__
#define __AC_ES_ENTITYOBSERVER_H__

#include "Types.h"

namespace ac
{
	namespace es
	{
		/// \class EntityObserver
		/// \brief A class that observes an Entity's state
		///
		/// Derive from this class if you wish to be notified for an Entity's state
		/// within various Scene objects.
		///
		/// \note
		/// This differs from an EntityManager class, as an EntityManager is owned by the Scene
		/// therefore, it will be destroyed by the Scene. Whereas an EntityObserver will be added to
		/// the Scene and if the Scene is destroyed the EntityObserver will not be destroyed. Therefore
		/// you will have to manage your own EntityObserver objects within your program.
		///
		/// \author
		class EntityObserver
		{
			friend class Scene; // friends to access protected notifcations
			
		public:
			
			/// Destructor
			virtual ~EntityObserver() = 0;
						
		protected:
			
			// EVENTS
			
			/// Occurs when an Entity is activated
			/// \param sender The Scene that sent this notifcation
			/// \param e The Entity that has been activated
			virtual void onEntityActivated(ScenePtr sender, EntityPtr e)	{}
			
			/// Occurs when an Entity is deactivated
			/// \param sender The Scene that sent this notifcation
			/// \param e The Entity that has been deactivated
			virtual void onEntityDeactivated(ScenePtr sender, EntityPtr e)	{}
			
			/// Occurs when an Entity was added to the Scene
			/// \param sender The Scene that sent this notifcation
			/// \param e The Entity that was added to the Scene
			virtual void onEntityAdded(ScenePtr sender, EntityPtr e)	{}
			
			/// Occurs when an Entity is removed from a Scene
			/// \param sender The Scene that sent this notification
			/// \param e The Enitty that was removed from the Scene
			virtual void onEntityRemoved(ScenePtr sender, EntityPtr e) {}
		};
	}
}

#endif // __AC_ES_ENTITYOBSERVER_H__