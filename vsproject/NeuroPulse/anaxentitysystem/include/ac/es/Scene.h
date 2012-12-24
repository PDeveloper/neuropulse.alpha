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


#ifndef __AC_ES_SCENE_H__
#define __AC_ES_SCENE_H__

#include <vector>

#include "EntityObserver.h"
#include "EntityFactory.h"
#include "ComponentContainer.h"
#include "EntityContainer.h"
#include "EntityManagerContainer.h"
#include "EntitySystemContainer.h"


namespace ac
{
	namespace es
	{
		/// \class Scene
		/// \brief A class that resembles a Scene, inside of your game
		///
		/// The Scene class holds and manages Entity objects, EntitySystem objects, EntityManager objects.
		/// A Scene is much like a World inside your game. The Scene may be updated, initialized and cleared.
		///
		/// \note
		/// Typically a Scene will be updated each frame (or whenever you require to update, e.g. 40FPS)
		///
		/// \author Miguel Martin
		class Scene
		{
			friend class EntityFactory;
			
		public:
			
			/// Default Constructor
			Scene();
			
			/// Destructor
			~Scene();
			
			/// Initializes the Scene
			void initialize();
			
			/// Updates the Scene
			void update();
			
			/// Clears the Scene
			void clear();
			
			/// Cleans the Scene from any build-up cache, this method
			/// should be used when you wish to make sure that all
			/// Entity objects within the Scene have been succesfully
			/// destroyed and so on.
			void clean();
			
			/// Creates an Entity and adds it automatically to the Scene
			/// \return A created Entity, for you to freely use
			/// \note You should store the return value in a variable, unless you want the Entity to do nothing,
			/// which doesn't really make any sense.
			EntityPtr createEntity();
			
			/// Inserts an Entity to the Scene
			/// \param entity The Entity you wish to add to the Scene
			void insertEntity(EntityPtr entity);
			
			/// Destroys an Entity
			/// \param entity The Entity you wish to destroy
			/// \note
			/// The Entity will be deleted from memory after
			/// the next call to update(), or clean()
			void eraseEntity(EntityPtr entity);
			
			/// Acitvates an Entity. Call this method if you change your Entity.
			/// \param entity The Entity you wish to add
			void activateEntity(EntityPtr entity);
			
			/// Deactivates an Entity. Call this method if you wish to make sure an
			/// Entity does not get processed by an EntitySystem.
			/// \param entity The Entity you wish to deactivate
			void deactivateEntity(EntityPtr entity);
			
			/// Determines whether an Entity is activated
			/// \return true if it is, false otherwise
			bool isEntityActivated(ConstEntityPtr entity) const;
			
			/// Determines if an Entity is alive
			///	(i.e. if destroyEntity(EntityPtr) has not been called
			/// \param entityId The Entity'd Id you wish to check for
			/// \return true if the Entity is alive, false otherwise
			bool isEntityAlive(const EntityId& entityId) const;
			
			/// Determines if an Entity is alive
			///	(i.e. if destroyEntity(EntityPtr) has not been called
			/// \param entity The Entity you wish to check for
			/// \return true if the Entity is alive, false otherwise
			bool isEntityAlive(ConstEntityPtr entity) const { return isEntityAlive(entity->getId()); }
			
			/// Inserts an EntityObserver to the Scene
			/// \param entityObserver The EntityObserver you wish to add
			void insertEntityObserver(EntityObserver* entityObserver);
			
			/// Erases an EntityObserver from the Scene
			/// \param entityObserver The EnttyObserver you wish to remove
			void eraseEntityObserver(EntityObserver* entityObserver);
			
			/// \param index The index you wish to 
			/// \return The EntityObserver at the specified index,
			///			or NULL if the index is out of bounds
			EntityObserver* getEntityObserver(size_t index) const;
			
			/// Determines if an EntityObserver exists within the Scene
			/// \param entityObserver The EntityObserver you wish to check for
			/// \return true if the Scene contains the entityObserver
			bool containsEntityObserver(EntityObserver* entityObserver) const;
			
			/// Inserts an EntitySytem to the Scene
			/// \tparam T Must be derived from the EntitySystem class
			/// \param entitySystem The EntitySystem you wish to insert
			/// \note The EntitySystem will BELONG to the Scene, and therefore
			/// if a Scene is destructed, the EntitySystems in the Scene will also be destructed
			template <typename T>
			void insertEntitySystem(T* entitySystem)
			{
				_entitySystemContainer.insert(entitySystem);
			}
			
			/// Erases an EntitySystem from the Scene
			/// \tparam T Must be derived from the EntitySystem class
			template <typename T>
			void eraseEntitySystem()
			{
				_entitySystemContainer.erase<T>();
			}
			
			/// Erases an EntitySystem from the Scene
			/// \tparam T Must be derived from the EntitySystem class
			/// \param entitySystem The EntitySystem you wish to erase from the Scene
			template <typename T>
			void removeEntitySystem(T* entitySystem)
			{
				_entitySystemContainer.erase(entitySystem);
			}
			
			/// Determines if the Scene contains an EntitySystem
			/// \tparam T Must be derived from the EntitySystem class
			/// \return true if the Scene does contain the EntitySystem, false otherwise
			template <typename T>
			bool containsEntitySystem() const
			{
				return _entitySystemContainer.contains<T>();
			}
			
			/// Determines if the Scene contains an EntitySystem
			/// \tparam T Must be derived from the EntitySystem class
			/// \param entitySystem The EntitySystem you wish to check for
			/// \return true if the Scene does contain the EntitySystem, false otherwise
			template <typename T>
			bool containsEntitySystem(T* entitySystem) const
			{
				return _entitySystemContainer.contains<T>(entitySystem);
			}
			
			/// Inserts an EntityManager into the Scene
			/// \tparam T Must be derived from the EntityManager class
			/// \param entityManager The EntityManager you wish to insert
			template <typename T>
			void insertEntityManager(T* entityManager)
			{
				_entityManagerContainer.insert(entityManager);
				insertEntityObserver(entityManager);
				entityManager->setScene(this);
			}
			
			/// Erases an EntityManager into the Scene
			/// \tparam T Must be derived from the EntityManager class
			template <typename T>
			void eraseEntityManager()
			{
				EntityManager* manager = _entityManagerContainer.get<T>();
				manager->setScene(NULL);
				eraseEntityObserver(manager);
				_entityManagerContainer.erase(T::GetClass());
			}
			
			/// Erases an EntityManager into the Scene
			/// \tparam T Must be derived from the EntityManager class
			/// \param entityManager The EntityManager you wish to erase
			template <typename T>
			void eraseEntityManager(T* entityManager)
			{
				entityManager->setScene(NULL);
				removeEntityObserver(entityManager);
				_entityManagerContainer.erase(entityManager);
			}
			
			/// Determines if the Scene contains an EntityManager
			/// \tparam T Must be derived from the EntityManger class
			/// \return true if the Scene does contain the EntityManager, false otherwise
			template <typename T>
			bool containsEntityManager() const
			{
				return _entityManagerContainer.contains<T>();
			}
			
			/// Determines if the Scene contains an EntityManager
			/// \tparam T Must be derived from the EntityManger class
			/// \param entityManager The EntityManager object you wish to check for
			/// \return true if the Scene does contain the EntityManager, false otherwise
			template <typename T>
			bool containsEntityManager(T* entityManager) const
			{
				return _entityManagerContainer.contains<T>(entityManager);
			}
			
			
			
			/// \return The EntityContainer object that is connected with the Scene
			const EntityContainer& getEntityContainer() const				{ return _entityContainer; }
			
			/// \return The EntitySystemContainer object that contains all EntitySystem objects within the Scene
			const EntitySystemContainer& getEntitySystemContainer() const	{ return _entitySystemContainer; }
			
			/// \return The EntityFactory attached to the Scene
			const EntityFactory& getEntityFactory() const					{ return _entityFactory; }
			
			/// \return The ComponentContainer that is attached to the Scene
			ComponentContainer& getComponentContainer()						{ return _componentContainer; }
			const ComponentContainer& getComponentContainer() const			{ return _componentContainer; }
			
			const EntityManagerContainer& getEntityManagerContainer() const { return _entityManagerContainer; }
			
		private:
			
			// UTILITY FUNCTIONS
			
			/// Processes the Entity objects that have been activated
			void processActivatedEntityCache();
			
			/// Processes the Entity objects that have been deactivated
			void processDeactivatedEntityCache();
			
			/// Processes the Entity objects that have been added to the Scene
			void processAddedEntityCache();
			
			/// Processes the Entity objects that have been removed from the Scene
			void processRemovedEntityCache();
			
			/// Clears all the Entity cache(s) in the Scene
			void clearEntityCache();
			
			
			
			typedef std::vector<EntityObserver*> EntityObserverArray;
			
			/// The EntityObserver objects that are attached to the Scene
			EntityObserverArray _entityObservers;
			
			/// The class that creates Entity objects within the Scene
			EntityFactory _entityFactory;
			
			/// The object that contains all the Entity objects within the Scene
			EntityContainer _entityContainer;
			
			/// The object that contains all Component objects for Entity
			/// objects within the Scene
			ComponentContainer _componentContainer;
			
			/// The object that contains all the EntitySystems within the Scene
			EntitySystemContainer _entitySystemContainer;
			
			/// The object that contains all the EntityManager objects within the Scene
			EntityManagerContainer _entityManagerContainer;
			
			// CACHE
			
			/// Holds Entity objects that have been activated
			EntityArray _entityActivatedCache;
			
			/// Holds Entity objects that have been deactivated
			EntityArray _entityDeactivatedCache;
			
			/// Holds Entity objects that have been added to the Scene
			EntityArray _entityAddedCache;
			
			/// Holds Entity objects that have been removed from the Scene
			EntityArray _entityRemovedCache;
			
			
			
			
			// Prevent from copying; purposely not defined
			Scene(const Scene&);
			const Scene& operator=(const Scene&);
		};
	}
}

#endif // __AC_ES_SCENE_H__