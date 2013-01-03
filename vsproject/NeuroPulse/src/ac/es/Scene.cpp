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


#include "Scene.h"

namespace ac
{
	namespace es
	{
		Scene::Scene()
		{
		}
		
		
		Scene::~Scene()
		{
			clear();
		}
		
		
		
		void Scene::initialize()
		{
			// initialize all the EntitySystem objects in the EntitySystemContainer
			for(EntitySystemContainer::iterator i = _entitySystemContainer.begin(); i != _entitySystemContainer.end(); ++i)
			{
				// is the pointer null?
				if(*i == NULL)
					continue;
				
				(*i)->initialize();
			}
			
			// initialize all the EntityManager objects in the EntityManagerContainer
			for(EntityManagerContainer::iterator i = _entityManagerContainer.begin(); i != _entityManagerContainer.end(); ++i)
			{
				// is the pointer null?
				if(*i == NULL)
					continue;
				
				(*i)->initialize();
			}
		}
		
		void Scene::update()
		{
			// clean the Scene
			clean();
			
			EntitySystemPtr entitySystem = NULL;
			// and then update the EntitySystem objects in the EntitySystemContainer
			for(EntitySystemContainer::iterator i = _entitySystemContainer.begin(); i != _entitySystemContainer.end(); ++i)
			{
				entitySystem = (*i).get();
				
				// is the pointer null? Or is it passive (it will be manually updated)
				if(entitySystem == NULL || entitySystem->isPassive())
					continue;
				
				(*i)->update();
			}
		}
		
		void Scene::clear()
		{
			// clean the Scene
			clean();
			
			// clear all da classes
			_entitySystemContainer.clear();
			_entityContainer.clear();
			_componentContainer.clear();
			_entityFactory.clearCountData();
		}
		
		void Scene::clean()
		{
			// process the cache
			processAddedEntityCache();
			processActivatedEntityCache();
			processDeactivatedEntityCache();
			processRemovedEntityCache();
			
			// clear the cache
			clearEntityCache();
			
			// clear the cache
			clearEntityCache();
		}
		
		
		
		EntityPtr Scene::createEntity()
		{
			EntityPtr entity = _entityFactory.createEntity(this);
			insertEntity(entity); // insert the Entity
			return entity;
		}
		
		void Scene::insertEntity(EntityPtr entity)
		{
			// insert it to the 
			_entityContainer.insert(entity);
			
			// add it to the cache, we'll process it later
			_entityAddedCache.push_back(entity);
		}
		
		void Scene::eraseEntity(EntityPtr entity)
		{
			// add it temporarily to a cache, we'll delete  it later
			_entityRemovedCache.push_back(entity);
		}
		
		void Scene::activateEntity(EntityPtr entity)
		{
			// if the Entity is already activated
			if(isEntityActivated(entity))
				return;
			
			// activate it in the Container
			_entityContainer.activate(entity);
			
			// add it temporarily to a cache, we'll activate it later
			_entityActivatedCache.push_back(entity);
		}
		
		void Scene::deactivateEntity(EntityPtr entity)
		{
			// if the Entity is not activated
			if(!isEntityActivated(entity))
				return;
			
			// activate it in the Container
			_entityContainer.deactivate(entity);
			
			// add it temporarily to a cache, we'll deactivate it later
			_entityDeactivatedCache.push_back(entity);
		}
		
		bool Scene::isEntityActivated(ConstEntityPtr entity) const
		{
			return _entityContainer.isActivated(entity);
		}
		
		bool Scene::isEntityAlive(const EntityId &entityId) const
		{
			return _entityContainer.contains(entityId);
		}
		
		void Scene::insertEntityObserver(EntityObserver* entityObserver)
		{
			_entityObservers.push_back(entityObserver);
		}
		
		void Scene::eraseEntityObserver(EntityObserver* entityObserver)
		{
			_entityObservers.erase(std::find(_entityObservers.begin(), _entityObservers.end(), entityObserver));
		}
		
		EntityObserver* Scene::getEntityObserver(size_t index) const
		{
			return _entityObservers[index];
		}
		
		bool Scene::containsEntityObserver(EntityObserver* entityObserver) const
		{
			return std::find(_entityObservers.begin(), _entityObservers.end(), entityObserver) != _entityObservers.end();
		}
		
		
		
		// UTILITY METHODS
		
		void Scene::processActivatedEntityCache()
		{
			EntityPtr entity = NULL;
			
			for(EntityArray::iterator i = _entityActivatedCache.begin(); i != _entityActivatedCache.end(); ++i)
			{
				entity = *i;
				
				// check the Entity with ALL the EntitySystem objects within the EntitySystemContainer
				for(EntitySystemContainer::iterator i = _entitySystemContainer.begin(); i != _entitySystemContainer.end(); ++i)
				{
					// is the pointer null?
					if(*i == NULL)
						continue;
					
					(*i)->check(entity);
				}
				
				// notify the EntityObservers
				for(EntityObserverArray::iterator i = _entityObservers.begin(); i != _entityObservers.end(); ++i)
				{
					// is the pointer null?
					if(*i == NULL)
						continue;
					
					(*i)->onEntityActivated(this, entity);
				}
			}
		}
		
		void Scene::processDeactivatedEntityCache()
		{
			EntityPtr entity = NULL;
			
			for(EntityArray::iterator i = _entityDeactivatedCache.begin(); i != _entityDeactivatedCache.end(); ++i)
			{
				entity = *i;
				
				// check the Entity with ALL the EntitySystem objects within the EntitySystemContainer
				for(EntitySystemContainer::iterator i = _entitySystemContainer.begin(); i != _entitySystemContainer.end(); ++i)
				{
					// is the pointer null?
					if(*i == NULL)
						continue;
					
					(*i)->check(entity);
				}
				
				// notify the EntityObservers
				for(EntityObserverArray::iterator i = _entityObservers.begin(); i != _entityObservers.end(); ++i)
				{
					// is the pointer null?
					if(*i == NULL)
						continue;
					
					(*i)->onEntityDeactivated(this, entity);
				}
			}
		}
		
		void Scene::processAddedEntityCache()
		{
			EntityPtr entity = NULL;
			
			for(EntityArray::iterator i = _entityAddedCache.begin(); i != _entityAddedCache.end(); ++i)
			{
				entity = *i;
				
				// check the Entity with ALL the EntitySystem objects within the EntitySystemContainer
				for(EntitySystemContainer::iterator i = _entitySystemContainer.begin(); i != _entitySystemContainer.end(); ++i)
				{
					// is the pointer null?
					if(*i == NULL)
						continue;
					
					(*i)->check(entity);
				}
				
				// notify the EntityObservers
				for(EntityObserverArray::iterator i = _entityObservers.begin(); i != _entityObservers.end(); ++i)
				{
					// is the pointer null?
					if(*i == NULL)
						continue;
					
					(*i)->onEntityAdded(this, entity);
				}
			}
		}
		
		void Scene::processRemovedEntityCache()
		{
			EntityPtr entity = NULL;
			
			for(EntityArray::iterator i = _entityRemovedCache.begin(); i != _entityRemovedCache.end(); ++i)
			{
				entity = *i;
				
				// check the Entity with ALL the EntitySystem objects within the EntitySystemContainer
				for(EntitySystemContainer::iterator i = _entitySystemContainer.begin(); i != _entitySystemContainer.end(); ++i)
				{
					// is the pointer null?
					if(*i == NULL)
						continue;
					
					(*i)->onRemovedFromScene(entity);
				}
				
				// notify the EntityObservers
				for(EntityObserverArray::iterator i = _entityObservers.begin(); i != _entityObservers.end(); ++i)
				{
					// is the pointer null?
					if(*i == NULL)
						continue;
					
					(*i)->onEntityRemoved(this, entity);
				}
				
				// erase it from the container
				_entityContainer.erase(entity);
			}
		}
		
		void Scene::clearEntityCache()
		{
			_entityActivatedCache.clear();
			_entityDeactivatedCache.clear();
			_entityAddedCache.clear();
			_entityRemovedCache.clear();
		}
	}
}