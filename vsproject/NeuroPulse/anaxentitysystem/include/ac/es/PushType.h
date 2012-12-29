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

#ifndef __AC_ES_PUSHTYPE_H__
#define __AC_ES_PUSHTYPE_H__

namespace ac
{
	namespace es
	{
		/// \struct PushType
		/// \brief A wrapper for the PushType enumeration
		///
		/// This data structure is defined so that it does not clutter
		/// the global namespace
		///
		/// \author Miguel Martin
		struct PushType
		{
		public:
			
			/// \enum Type
			/// \brief Describes how you want to push a Scene onto a Scene stack
			///
			/// This enumeration contains various values on how you may push a Scene on a Scene stack, this was
			/// specifically designed for the SceneDirector class.
			///
			/// \author Miguel Martin
			enum Type
			{
				/// Pushes on the new scene, and pops off the
				/// last scene that was pushed on the Scene
				/// stack, if there is one.
				PushAndPop,
				/// Pushes on the new scene,
				/// and pops off all previous scenes on the Scene stack
				PushAndPopAllPreviousScenes,
				/// Pushes on the new scene, without popping off the last scene
				PushWithoutPopping,
				/// Pushes on the new scene, without popping off the last scene
				/// Unlike the previous enumeration, this enumeration makes it so that
				/// the previous is still updated, whilst the new scene is updated
				PushWithoutPoppingSilenty
			};
		};
	}
}


#endif // __AC_ES_PUSHTYPE_H__