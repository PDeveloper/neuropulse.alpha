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

#ifndef __AC_ES_ENTITYSYSTEM_H__
#define __AC_ES_ENTITYSYSTEM_H__

#include <vector>

#include "../Identfiable.h"
#include "../ObjectFactory.h"

#include "ComponentFilter.h"
#include "Entity.h"
#include "EntityObserver.h"

namespace ac
{
	namespace es
	{
		class Scene;
		
		/// \class EntitySystem
		/// \brief An abstract class that describes a system in the Entity System
		///
		/// A system in a typical Entity System describes the logic of how entities with specific components
		/// are used within a Scene. An example EntitySystem would be a MovementSystem, where Entity objects with
		/// position and velocity components would be processed.
		///
		/// \author Miguel Martin
		class EntitySystem
		{
			friend class Scene;
			
			AC_IDENTIFIABLE_BASE(EntitySystem)
			
		public:
			
			/// Creates an EntitySystem, through the use of a string
			/// \param name The class name of the EntitySystem you wish
			///				to instantiate
			/// \return The created EntitySystem, OR a NULL pointer if the
			///			class name does not exsist.
			static EntitySystemPtr Create(const std::string& name)
			{
				// create the object
				return ac::object_factory::create<EntitySystem>(name);
			}
			
			/// Destroys an EntitySystem
			/// \param entitySystem The EntitySystem object you wish to destroy
			/// \note
			/// It is suggested to use this, instead of delete. It is not
			/// reccomended to actually call this method manually, the
			/// EntitySystemManager should handle this.
			static void Destroy(EntitySystemPtr entitySystem)
			{
				// destroy the component
				ac::object_factory::destroy(entitySystem);
			}
			
			
			
			/// Default Constructor
			EntitySystem();
			
			/// Constructs an EntitySystem
			/// \param componentFilter The ComponentFilter you wish to construct the EntitySystem with
			EntitySystem(const ComponentFilter& componentFilter);
			
			/// Destructor
			virtual ~EntitySystem() = 0;
			
			
			
			/// Updates the EntitySystem
			void update();
			
			/// Determines whether the EntitySystem contains an Entity
			/// \param e The Entity you wish to check for
			/// \return true if the EntitySystem does
			bool contains(ConstEntityPtr e) const;
			
			/// Determines whether the EntitySystem is interested in an Entity
			/// \return true if it is, false otherwise
			bool isInterested(ConstEntityPtr e) const;
			
			/// Enables the EntitySystem
			void enable() { setIsEnabled(true); }
			
			/// Disables the EntitySystem
			void disable() { setIsEnabled(false); }
			
			/// Sets the isEnabled flag
			/// \param value The value which you wish to have
			void setIsEnabled(bool value) { _isEnabled = value; }
			
			/// \return true if the EntitySystem is enabled, false otherwise
			bool isEnabled() const { return _isEnabled; }
			
			/// Sets the isPassive flag, which determines whether the EntitySystem will get updated
			/// inside an EntitySystemContainer class.
			/// \param value true if you wish to update the EntitySystem youself, false if you wish
			///				 the EntitySystem to udpate itself
			void setIsPassive(bool value) { _isPassive = value; }
			
			/// \return true if the EntitySystemContainer will update this EntitySystem
			bool isPassive() const { return _isPassive; }
			
			/// \return The entities to process
			const EntityArray& getEntitiesToProcess() const	{ return _entitiesToProcess; }
			
			/// Sets the ComponentFilter that the EntitySystem will have
			/// \param componentFilter The filter you wish to apply to the Entitysystem
			void setComponentFilter(const ComponentFilter& componentFilter) { _componentFilter = componentFilter; }
			
			/// \return The ComponentFilter that is applied to the EntitySystem
			const ComponentFilter& getComponentFilter() const				{ return _componentFilter; }
			
		protected:
			
			/// Initializes the EntitySystem
			virtual void initialize() {}
			
			/// Occurs when the EntitySystem is about to process entities
			virtual void onBeginProcessing() {}
			
			/// Processes Entity objects
			/// \param entities The entities that will be processed
			virtual void processEntities(const EntityArray& entities) { }
			
			/// Occurs when the EntitySystem is finished processing the entities
			virtual void onEndProcessing() {}
			
			/// Determines whether the EntitySystem should process Entity objects within the system
			/// \return true if it should, false otherwise
			/// \note By default this will return true to continue processing Entity objects
			virtual bool shouldProcessEntities() { return true; }
			
			/// An event that occurs when an Entity is added to the EntitySystem
			virtual void onAddedEntity(EntityPtr e) {}
			
			/// An event that occurs when an Entity is removed from the EntitySystem
			/// \param entity The Entity that is removed from the system
			virtual void onRemovedEntity(EntityPtr e) {}
			
		private:
			
			/// Checks if the Entity is viable to be added to the EntitySystem
			/// If it is, then it will be added to the EntitySystem
			void check(EntityPtr e);
			
			/// Inserts an Entity to the EntitySystem
			/// \param e The Entity you wish to insert
			void insert(EntityPtr e);
			
			/// Removes an Entity from the EntitySystem
			/// \param e The Entity you wish to remove
			void remove(EntityPtr e);
			
			/// An event that occurs when an Entity is removed from a Scene
			/// \param e The Entity that is removed from the Scene
			void onRemovedFromScene(EntityPtr e);
			
			
			
			/// Determines whether the EntitySystem will be automatically updated
			/// within an EntitySystemContainer
			bool _isPassive;
			
			/// Determines whether the EntitySystem is enabled or not
			bool _isEnabled;
			
			/// The object that is used to help filter out Component objects
			ComponentFilter _componentFilter;
			
			/// Contains all the entities to process
			EntityArray _entitiesToProcess;
			
			
			
			// Prevent from copying; purposely not defined
			EntitySystem(const EntitySystem&);
			const EntitySystem& operator=(const EntitySystem&);
		};
		
		
		/// Used for readability
		typedef EntitySystem::Class EntitySystemType;
	}
}

/// Declares a class to be an EntitySystem
/// If you create a new EntitySystem class you MUST put this macro
/// inside the class. NO EXCEPTIONS
#define AC_ES_ENTITY_SYSTEM(class) AC_IDENTIFIABLE(class)

/// Registers an EntitySystem class, this is used for instantiating
/// EntitySystems through a string.
#define AC_ES_REGISTER_ENTITY_SYSTEM(class) AC_CLASS_REGISTER(ac::es::EntitySystem, class)


#endif // __AC_ES_ENTITYSYSTEM_H__