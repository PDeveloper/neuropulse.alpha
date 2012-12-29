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

#ifndef __AC_ES_ENTITYMANAGER_H__
#define __AC_ES_ENTITYMANAGER_H__

#include "../Identfiable.h"
#include "../ObjectFactory.h"

#include "Types.h"
#include "EntityObserver.h"

namespace ac
{
	namespace es
	{		
		/// \class EntityManager
		/// \brief An abstract class that can manage Entities
		///
		/// This class is designed to manage Entity objects within a Scene.
		///
		/// \note
		/// If you derive from this class, please be warned that if a Scene object is destroyed,
		/// any EntityManager objects attached to the Scene will also be destroyed. If you wish
		/// to be notified on an Entity's state, but wish to keep the object that is notified alive, please
		/// see the EntityObserver class.
		///
		/// \author Miguel Martin
		class EntityManager
			: public EntityObserver
		{
			friend class Scene;
			
			AC_IDENTIFIABLE_BASE(EntityManager)
			
		public:
			
			/// Creates an EntityManager, through the use of a string
			/// \param name The class name of the EntityManager you wish
			///				to instantiate
			/// \return The created EntityManager, OR a NULL pointer if the
			///			class name does not exsist.
			static EntityManagerPtr Create(const std::string& name)
			{
				// create the object
				return ac::object_factory::create<EntityManager>(name);
			}
			
			/// Destroys an EntityManager object
			/// \param entityManager The EntityManager you wish to destroy
			/// \note
			/// It is suggested to use this, instead of delete. It is not
			/// reccomended to actually call this method manually, the
			/// EntitySystemManager should handle this.
			static void Destroy(EntityManagerPtr entityManager)
			{
				// destroy the component
				ac::object_factory::destroy(entityManager);
			}
			
			/// Destructor
			virtual ~EntityManager() = 0;
			
			/// \return The Scene that the EntityManager object is connected to
			ScenePtr getScene() const
			{
				return _scene;
			}
			
		protected:
			
			/// Initializes the EntityManager
			virtual void initialize() {}
			
		private:
			
			/// Sets the Scene
			/// \param scene The Scene you wish to connect to
			/// \note This will be called by a Scene, once an EntityManager has been added to it
			void setScene(ScenePtr scene)
			{
				_scene = scene;
			}
			
			
			/// The Scene that the Manager is connected to
			ScenePtr _scene;
		};
	}
}

#define AC_ES_ENTITY_MANAGER(manager) AC_IDENTIFIABLE(manager)

#define AC_ES_REGISTER_ENTITY_MANAGER(manager) AC_CLASS_REGISTER(ac::es::EntityManager, manager)

#endif // __AC_ES_ENTITYMANAGER_H__