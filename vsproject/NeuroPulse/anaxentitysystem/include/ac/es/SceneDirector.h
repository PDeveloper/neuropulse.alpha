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

#ifndef __AC_ES_SCENEDIRECTOR_H__
#define __AC_ES_SCENEDIRECTOR_H__

#include <vector>

#include "../Config.h"

#include "Scene.h"
#include "PushType.h"
#include "SceneDirectorDelegate.h"

#ifdef AC_NO_CPP11_LIBS
#	include <boost/shared_ptr.hpp>
#else
#	include <memory>
#endif

namespace ac
{
	namespace es
	{
		/// \class SceneDirector
		/// \brief A class that directs multiple Scene objects
		///
		/// The SceneDirector acts as a stack of Scene objects. A Scene may be pushed
		/// onto a stack, with various options. This class has a delegate class SceneDirectorDelegate,
		/// which allows for notifcations when a Scene will be pushed/removed from the stack, etc.
		///
		/// \see PushType for the various options for pushing on the Scene stack
		///
		/// \author Miguel Martin
		class SceneDirector
		{
			typedef
#	ifdef AC_NO_CPP11_LIBS
			boost::
#	else
			std::
#	endif
			shared_ptr<Scene> ScenePtrImpl;
			
		public:
			
			/// A pair used for the SceneStack, to determine
			/// what type of push type that the scene pair was pushed with
			typedef std::pair<ScenePtrImpl, PushType::Type> ScenePair;
			
			/// Resembles a stack/array of Scenes
			/// Use the method back() to retrieve the top of the stack
			/// The first element resembles the scene, and the second element
			/// resembles how the scene was pushed on.
			///
			/// \note
			/// If you pushed a Scene on silently, you may make it not silent
			/// by changing the type of push that it is marked it;
			/// the same works vise versia.
			typedef std::vector<ScenePair> SceneStack;
			
			
			
			/// Default constructor
			/// Constructs the SceneDirector with no scenes added to it
			SceneDirector();
			
			/// Adds a Scene to the SceneDirector once constructed
			/// \param scene The Scene you wish to start off with
			SceneDirector(ScenePtr scene);
			
			/// Uses a pre-built Scene Stack to update
			/// \param sceneStack The stack of scenes that you wish to manage
			SceneDirector(const SceneStack& sceneStack);
			
			/// Destructor
			~SceneDirector();
			
			
			
			/// Sets the Delegate of the Scene Director
			/// \param delegate The delegate you wish to assign for notification call-backs
			void setDelegate(SceneDirectorDelegate* delegate) { _delegate = delegate; }
			
			/// \return The delegate of the SceneDirector
			SceneDirectorDelegate* getDelegate() const { return _delegate; }
			
			/// Pushes a scene on the Scene stack
			/// \param scene The scene you wish to push on the stack
			/// \param pushType 
			void push(ScenePtr scene, PushType::Type pushType = PushType::PushAndPop);
			
			/// Pops off the last Scene that was pushed onto the Scene stack
			void pop();
			
			/// Removes a scene from the Scene stack
			/// \param scene The Scene you wish to remove
			void remove(ScenePtr scene);
			
			/// \return The stack of Scene objects that this class manages
			const SceneStack& getSceneStack() const;
			
			/// Updates the required scenes in the manager
			void update();
			
			// Clears the SceneDirector
			void clear();
			
		private:
			
			/// The scenes that the SceneDirector manages
			SceneStack _scenes;
			
			/// The delegate for the SceneDirector
			SceneDirectorDelegate* _delegate;
		};
	}
}

#endif // __AC_ES_SCENEDIRECTOR_H__