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

#ifndef __AC_ES_COMPONENT_H__
#define __AC_ES_COMPONENT_H__

#include "../Identfiable.h"
#include "../ObjectFactory.h"

namespace ac
{
	namespace es
	{
		/// \class Component
		/// \brief An abstract class that defines a Component
		///
		/// This class is a component, which is used to wrap data
		/// with, in order to 
		/// 
		/// \author Miguel Martin
		class Component
		{
			AC_IDENTIFIABLE_BASE(Component)
			
		public:
			
			/// Pure virtual destructor
			virtual ~Component() = 0;
			
			EntityPtr parent;
			
			/// Creates a component, through the use of a string
			/// \param name The class name of the Component you wish to instantiate
			/// \return The created Component, OR a NULL pointer if the class name does not exsist.
			static Component* Create(const std::string& name);
			
			/// Destroys a Component
			/// \param component The component you wish to destroy
			/// \note
			/// It is suggested to use this, instead of delete. It is not
			/// reccomended to actually call this method manually, the
			/// ComponentManager should handle this.
			static void Destroy(Component* component);
		};
		
		/// Used for readability
		typedef Component::Class ComponentType;
	}
}


/// Declares a class to be a Component
/// If you create a new Component class you MUST put this macro
/// inside the class. NO EXCEPTIONS
/// e.g.
/// \code
/// class VelocityComponent
///		: public Component
/// {
///		AC_ES_COMPONENT(VeclotityComponent)
///		// NOTICE THIS LINE ^^^
/// public:
///		explicit VelocityComponent(Vector3 velocity = Vector3())
///			: _velocity(velocity) {}
///
///		Vector3 getVelocity() { return _velocity; }
///		void setVelocity(const Vector3& velocity) { _velocity = velocity; }
///
///	private:
///		Vector3 _velocity;
/// };
/// \endcode
#define AC_ES_COMPONENT(class) AC_IDENTIFIABLE(class)

/// Registers a Component class, this is used for instantiating
/// components through a string.
/// \note
/// It is suggested to place this macro OUTSIDE the namespace(s) that your
/// custom component is inside. This is to reduce naming collisions.
/// For example
/// \code
/// namespace example_namespace
/// {
///		class ExampleComponent
///			: public Component
///		{
///			AC_ES_COMPONENT(ExampleComponent)
///		public:
///			// getters/setters/etc.
///		};
/// }
///
/// AC_ES_REGISTER_COMPONENT(example_namespace::ExampleComponent)
/// // NOTICE that the macro is OUTSIDE the namespace
///
/// \endcode
#define AC_ES_REGISTER_COMPONENT(class) AC_CLASS_REGISTER(ac::es::Component, class)


#endif // __AC_ES_COMPONENT_H__