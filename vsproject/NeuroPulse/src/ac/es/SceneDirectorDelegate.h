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

#ifndef __AC_ES_SCENEDIRECTORDELEGATE_H__
#define __AC_ES_SCENEDIRECTORDELEGATE_H__

namespace ac
{
	namespace es
	{
		class Scene;
		class SceneDirector;
		
		/// \class SceneDirectorDelegate
		/// \brief A class that is used for call-backs for the SceneDirector class
		///
		/// Inherit from this class if you wish to be notified of events from the SceneDirector class.
		///
		/// \author Miguel Martin
		class SceneDirectorDelegate
		{
		public:
			
			/// Destructor
			virtual ~SceneDirectorDelegate() = 0;
			
			/// Occurs when a Scene will be initialized
			/// \param sender The SceneDirector that sent this notification
			/// \param scene The Scene that will be initialized
			virtual void onSceneWillBeInitialized(SceneDirector* sender, Scene& scene) {}
			
			/// Occurs when a Scene has been initiailized
			/// \param sender The SceneDirector that sent this notification
			/// \param scene The Scene that has been initialized
			virtual void onSceneHasBeenInitialized(SceneDirector* sender, Scene& scene) {}
			
			/// Occurs when a Scene will die (i.e. be destroyed)
			/// \param sender The SceneDirector that sent this notification
			/// \param scene The Scene that will die
			virtual void onSceneWillDie(SceneDirector* sender, Scene& scene) {}
			
			/// Occurs when a Scene will be added to the Scene stack in the SceneDirector
			/// \param sender The SceneDirector that sent this notification
			/// \param scene The Scene that will be added to the stack
			virtual void onSceneWillBeAddedToStack(SceneDirector* sender, Scene& scene) {}
			
			/// Occurs when a Scene has been added to the Scene stack in the SceneDirector
			/// \param sender The SceneDirector that sent this notification
			/// \param scene The Scene that has been added to the stack
			virtual void onSceneHasBeenAddedToStack(SceneDirector* sender, Scene& scene) {}
		};
	}
}

#endif // __AC_ES_SCENEDIRECTORDELEGATE_H__