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

#include "ComponentContainer.h"

#include <cassert>

#include "util/DynamicArrayUtils.h"
#include "Entity.h"

namespace ac
{
	namespace es
	{
		namespace util
		{
			class ComponentDeleterFunctor
			{
			public:
				
				void operator()(ComponentPtr component) const
				{
					Component::Destroy(component);
				}
			};
		}
		
		ComponentContainer::ComponentContainer()
		{
			/* do nothing */
		}
		
		ComponentContainer::~ComponentContainer()
		{
			/* do nothing */
		}
		
		
		
		void ComponentContainer::addComponent(EntityPtr e, ComponentPtr component)
		{
			// add the component
			addComponent(e, component, component->getClass());
		}
		
		void ComponentContainer::addComponent(EntityPtr e, ComponentPtr component, const ComponentType& componentType)
		{
			assert(e != NULL);
			
			EntityId entityId = e->getId(); // holds the Entity's ID value
			ComponentType::Id componentTypeId = componentType.getId(); // holds the componentType's ID value
			
			// Resize the componentsForEntities array, if necesary
			util::EnsureCapacity(_componentsForEntities, entityId);
			
			// Store the components for the Entity, in a temporary array.
			ImplComponentArray& componentsForEntity = _componentsForEntities[entityId];
			// resize our components, if necesary 
			util::EnsureCapacity(componentsForEntity, componentTypeId);
			
			// contains the component we have to assign
			SmartComponentPtr& componentToAssign = componentsForEntity[componentTypeId];
			
			// if there is not a component with the same type there already,
			// and it's not the same component
			if(!componentToAssign)
			{
				// then we'll assign it (i.e. add it to the cache)
				// and we'll use a custom deleter
 				componentToAssign.reset(component, util::ComponentDeleterFunctor());
				
				// AND set the componentBit in the Entity for the componentType's ID
				util::AssignBitsetIndexWithAutoResize(e->_componentBits, componentTypeId, true);
			}
			// if the component that was passed in isn't the same as the componentToAssign
			else if(componentToAssign.get() != component)
			{
				// then we'll delete the component manually (for no memory leaks)
				util::ComponentDeleterFunctor()(component);
			}
		}
		
		void ComponentContainer::destroyComponent(EntityPtr e, ComponentPtr component)
		{
			destroyComponent(e, component, component->getClass());
		}
		
		void ComponentContainer::destroyComponent(EntityPtr e, ComponentPtr component, const ComponentType& componentType)
		{
			assert(e != NULL && e->getId() < _componentsForEntities.size());
			SmartComponentPtr& componentToRemove = _componentsForEntities[e->getId()][componentType.getId()];
			
			// does the two components have the same address?
			if(componentToRemove.get() == component)
			{
				// destroy it...
				componentToRemove.reset();
				
				// set the bitset in the Entity to false
				e->_componentBits[componentType.getId()] = false;
			}
		}
		
		void ComponentContainer::destroyComponent(EntityPtr e, const ComponentType& componentType)
		{
			assert(e != NULL && e->getId() < _componentsForEntities.size());
			
			EntityId entityId = e->getId(); // holds the Entity's ID
			ComponentType::Id componentTypeId = componentType.getId(); // holds the ComponentType's ID
			
			// get a reference to the component we need to remove and reset the pointer
			_componentsForEntities[entityId][componentTypeId].reset();
			
			// set the bitset in the Entity to false
			e->_componentBits[componentTypeId] = false;
		}
		
		void ComponentContainer::destroyAllComponents(EntityPtr e)
		{
			assert(e != NULL && e->getId() <= _componentsForEntities.size());
			_componentsForEntities[e->getId()].clear();
			
			// clear the bits in the Entity's ComponentBits
			e->_componentBits.clear();
		}
		
		
		ComponentPtr ComponentContainer::getComponent(ConstEntityPtr e, const ComponentType& componentType) const
		{
			if(e == NULL || e->getComponentBits().size() <= componentType.getId()) return NULL; // doesn't exist
			return _componentsForEntities[e->getId()][componentType.getId()].get();
		}
		
		bool ComponentContainer::containsComponent(ConstEntityPtr e, ComponentPtr component) const
		{
			return containsComponent(e, component, component->getClass());
		}
		
		bool ComponentContainer::containsComponent(ConstEntityPtr e, ComponentPtr component, const ComponentType& componentType) const
		{
			return getComponent(e, componentType) == component;
		}
		
		bool ComponentContainer::containsComponent(ConstEntityPtr e, const ComponentType& componentType) const
		{
			return getComponent(e, componentType) != NULL;
		}
		
		ComponentArray ComponentContainer::getComponentsFor(ConstEntityPtr e) const
		{
			assert(e != NULL && e->getId() < _componentsForEntities.size());
			ComponentArray components;
			const ImplComponentArray& componentsForEntity = _componentsForEntities[e->getId()];
			
			// loop through all the turned on bits in the Component
			DynamicBitSet::size_type index = e->getComponentBits().find_first();
			for(; index != DynamicBitSet::npos; index = e->getComponentBits().find_next(index))
			{
				// use the index to 
				components.push_back(componentsForEntity[index].get());
			}
			
			return components;
		}
		
		void ComponentContainer::clear()
		{
			_componentsForEntities.clear();
		}
	}
}