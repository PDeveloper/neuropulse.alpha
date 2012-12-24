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

#ifndef __AC_ES_ENTITY_H__
#define __AC_ES_ENTITY_H__

#include "Types.h"
#include "Component.h"
#include "ComponentContainer.h"

namespace ac
{
	namespace es
	{
		class Scene;
		class EntitySystem;
		class ComponentContainer;
		class EntityContainer;
		
		/// \class Entity
		/// \brief An Entity that is used for a game
		///
		/// An Entity (a.k.a. GameObject)
		///
		/// \note
		/// You must use an EntityFactory to create Entity objects
		///
		/// \author Miguel Martin
		class Entity
		{
			friend class EntityFactory;			// To construct an Entity object
			friend class EntitySystem;			// To change the SystemBits
			friend class ComponentContainer;	// To change the ComponentBits
			friend class EntityContainer;		// To assign the ID
			
		public:
			
			/// Destructor
			~Entity();
			
			
			/// \return The ID that the Entity has
			const EntityId& getId() const;
			
			/// \return The Scene in which the Entity is within
			ScenePtr getScene() const;
			
			/// \return The bits that determine whether
			/// this Entity is within an EntitySystem
			const DynamicBitSet& getSystemBits() const;
			
			/// \return The bits that determine whether
			/// this Entity contains a Component or not
			const DynamicBitSet& getComponentBits() const;
			
			/// Activates the Entity
			void activate();
			
			/// Deactivates the Entity
			void deactivate();
			
			/// Sets the isActivated flag to be true or false
			/// \param isActivated true if you want the Entity
			///					   to be activated, false otherwise
			void setIsActivated(bool isActivated);
			
			/// \return true if you wish to enable the Entity
			bool isActivated() const;
			
			/// Kills the Entity; the Entity should no longer be used after this method is called.
			void kill();
			
			/// \return true if the Entity is alive
			bool isAlive() const;
			
			/// Adds a Component to the Entity
			/// \tparam T The type of Component you wish to add
			/// \param component The component you wish to add
			/// \note T must NOT be the type Component
			template <typename T>
			void addComponent(T* component)
			{
				getComponentContainer().addComponent(this, component);
			}
			
			/// Destroys a Component from an Entity
			/// \tparam T The type of Component you wish to destroy
			template <typename T>
			void destroyComponent()
			{
				getComponentContainer().destroyComponent(this, T::GetClass());
			}
			
			/// Destroys a Component from an Entity
			/// \tparam T The type of Component you wish to destroy
			/// \param component The component you wish to destroy
			template <typename T>
			void destroyComponent(T* component)
			{
				getComponentContainer().destroyComponent(this, component);
			}
			
			/// Determines whether an Entity contains a Component
			/// \tparam T The type of Component you wish to check for
			/// \return true if the Entity contains the Component
			template <typename T>
			bool containsComponent() const
			{
				return getComponentContainer().containsComponent(this, T::GetClass());
			}
			
			/// Determines whether an Entity contains a Component
			/// \tparam T The type of Component you wish to check for
			/// \param component The Component you wish to check for
			/// \return true if the Entity contains the Component
			template <typename T>
			bool containsComponent(T* component) const
			{
				return containsComponent(component);
			}
			
			/// Obtains a Component from an Entity
			/// \tparam T The type of component you wish to retrieve
			/// \return The Component you wish to retrieve, or null if the type does not exsist within the Entity
			template <typename T>
			T* getComponent()
			{
				return static_cast<T*>(getComponent(T::GetClass()));
			}
			
			/// Obtains a Component from an Entity
			/// \param componentType The type of component you wish to retrieve
			/// \return The Component you wish to retrieve, or null if the type does not exsist within the Entity
			ComponentPtr getComponent(const ComponentType& componentType) const;
			
			/// \return All the Components that the Entity contains
			ComponentArray getComponents() const;
			
			/// \return The ComponentContainer object that the Entity is linked to
			ComponentContainer& getComponentContainer() const;
			
		private:
			
			/// \param scene The Scene that the Entity belongs to
			/// \param Id The ID you wish to have the Entity to have
			Entity(ScenePtr scene, ComponentContainer* componentContainer);
			
			
			
			/// The identifier of the Entity
			EntityId _id;
			
			/// The scene that the Entity belongs to
			ScenePtr _scene;
			
			/// The ComponentContainer the Entity is attached to
			ComponentContainer* _componentContainer;
			
			/// This determines whether this Entity is within an EntitySystem
			DynamicBitSet _systemBits;
			
			/// This determines whether an Entity has Components or not
			DynamicBitSet _componentBits;
			
			
			
			// Prevent from copying; purposely not defined
			Entity(const Entity&);
			const Entity& operator=(const Entity&);
		};
	}
}

#endif // __AC_ES_ENTITY_H__