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

#include "Entity.h"

#include "Scene.h"

namespace ac
{
	namespace es
	{
		Entity::Entity(Scene* scene, ComponentContainer* componentContainer)
			:	_scene(scene),
				_componentContainer(componentContainer),
				_componentBits(false),
				_systemBits(false)
		{
			/* do nothing */
		}
		
		Entity::~Entity()
		{
			/* do nothing */
		}
		
		
		
		const EntityId& Entity::getId() const
		{
			return _id;
		}
		
		ScenePtr Entity::getScene() const
		{
			return _scene;
		}
		
		const DynamicBitSet& Entity::getSystemBits() const
		{
			return _systemBits;
		}
		
		const DynamicBitSet& Entity::getComponentBits() const
		{
			return _componentBits;
		}
		
		void Entity::activate()
		{
			getScene()->activateEntity(this);
		}
		
		void Entity::deactivate()
		{
			getScene()->deactivateEntity(this);
		}
		
		void Entity::setIsActivated(bool isActivated)
		{
			
		}
		
		bool Entity::isActivated() const
		{
			return getScene()->isEntityActivated(this);
		}
		
		void Entity::kill()
		{
			getScene()->eraseEntity(this);
		}
		
		bool Entity::isAlive() const
		{
			return getScene()->isEntityAlive(this);
		}
		
		ComponentPtr Entity::getComponent(const ComponentType& componentType) const
		{
			return _componentContainer->getComponent(this, componentType);
		}
		
		ComponentArray Entity::getComponents() const
		{
			return _componentContainer->getComponentsFor(this);
		}
		
		ComponentContainer& Entity::getComponentContainer() const
		{
			return *_componentContainer;
		}
	}
}