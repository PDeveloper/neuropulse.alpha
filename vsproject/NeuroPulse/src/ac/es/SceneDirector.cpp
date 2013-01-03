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

#include "SceneDirector.h"

namespace ac
{
	namespace es
	{
		SceneDirector::SceneDirector()
            : _delegate(NULL)
		{
			
		}
		
		
		SceneDirector::SceneDirector(ScenePtr scene)
            : _delegate(NULL)
		{
			push(scene);
		}
		
		
		SceneDirector::SceneDirector(const SceneDirector::SceneStack& sceneStack)
			: _scenes(sceneStack),
              _delegate(NULL)
		{
		}
		
		
		SceneDirector::~SceneDirector()
		{
		}
		
		
		
		void SceneDirector::push(ScenePtr scene, PushType::Type pushType)
		{
			assert(scene != NULL);
			
			if(getDelegate())
			{
				getDelegate()->onSceneWillBeAddedToStack(this, *scene);
			}
			
			_scenes.push_back(ScenePair(scene, pushType));
			
			if(getDelegate())
			{
				getDelegate()->onSceneHasBeenAddedToStack(this, *scene);
			}
			
			if(getDelegate())
			{
				getDelegate()->onSceneWillBeInitialized(this, *scene);
			}
			
			// initialize the scene
			scene->initialize();
			
			if(getDelegate())
			{
				getDelegate()->onSceneHasBeenInitialized(this, *scene);
			}
		}
		
		void SceneDirector::pop()
		{
			if(getDelegate())
			{
				getDelegate()->onSceneWillDie(this, *_scenes.back().first);
			}
			_scenes.pop_back();
		}
		
		void SceneDirector::remove(ScenePtr scene)
		{
			// loop through all the scenes in the array
			for(SceneStack::iterator i = _scenes.begin(); i != _scenes.end(); ++i)
			{
				// if we have a match
				if(i->first.get() == scene)
				{
					if(getDelegate())
					{
						getDelegate()->onSceneWillDie(this, *i->first.get());
					}
					
					// erase the crap out of it
					_scenes.erase(i);
					
					
					break; // break out of the loop
				}
			}
		}
		
		const SceneDirector::SceneStack& SceneDirector::getSceneStack() const
		{
			return _scenes;
		}
		
		void SceneDirector::update()
		{
			// we're going to loop through the scenes backwards
			// if the top is silently pushed on, we will iterate again
			for(size_t i = _scenes.size(); i-- > 0;)
			{
				// update the scene
				_scenes[i].first->update();
				
				// if we no longer need to continue to iterate
				if(_scenes[i].second != PushType::PushWithoutPoppingSilenty)
				{
					break; // break out of the loop
				}
			}
		}
		
		void SceneDirector::clear()
		{
			_scenes.clear();
		}
	}
}