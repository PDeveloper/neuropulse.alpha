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

#ifndef __AC_OBJECTFACTORY_H__
#define __AC_OBJECTFACTORY_H__

#include <map>
#include <string>
#include <algorithm>

#define ANAX_OBJECT_FACTORY_VERSION_MAJOR 1
#define ANAX_OBJECT_FACTORY_VERSION_MINOR 0

namespace ac
{
	// This allows the use of allocating an object, through a string
	// e.g.
	// Object* obj = create<Object>("Banana"); // creates a banana
	//
	// inspired from:
	// http://gamedev.stackexchange.com/questions/17746/entity-component-systems-in-c-how-do-i-discover-types-and-construct-component
	//
	//
	// In order to able to do this... you MUST register the class and it CANNOT be an abstract class
	// To register a class, you use the AC_CLASS_REGISTER or AC_CLASS_REGISTER_WITH_NAME macro
	// e.g.
	// class Base { virtual ~Base() {} };
	// class Example : public Base { };
	// AC_CLASS_REGISTER(Base, Example)
	namespace object_factory
	{
		/// \class ClassRegistryData
		/// \brief Data that defines how an object is destroyed/created
		///
		/// This class basically "wraps" the allocation/deallocation of an object,
		/// through the use of function points.
		///
		/// \author Miguel Martin
		template <typename Base>
		class ClassRegistryData
		{
		public:
			
			/// The base class for the data
			typedef Base BaseClass;
			
			/// A typedef for a function that creates an object
			/// which is derived from the class Base
			typedef Base* (*CreatorFn)();
			/// Destroys an object that is derived from the class Base
			typedef void (*DestroyFn)(Base*);
			
			ClassRegistryData()
			{
				
			}
			
			ClassRegistryData(CreatorFn cFn, DestroyFn dFn)
			: createFn(cFn), destroyFn(dFn)
			{
			}
			
			/// Creates an object which is derived from the class Base
			CreatorFn createFn;
			
			/// Destroys an object that is derived from the class Base
			DestroyFn destroyFn;
		};
		
		namespace util
		{
			/// \struct AllocatorFunctor
			/// \brief The object which creates object
			///
			/// By default, this struct uses new to allocate objects.
			/// If however you wish to change how your object is allocated, simply
			/// implement a template specializtion of this class.
			///
			/// \author Miguel Martin
			template<typename Base, typename T>
			struct AllocatorFunctor
			{
				static Base* create()
				{
					return new T;
				}
			};
			
			/// \struct DeallocatorFunctor
			/// \brief The object which creates object
			///
			/// By default, this struct uses new to allocate objects.
			/// If however you wish to change how your object is allocated, simply
			/// implement a template specializtion of this class.
			///
			/// \author Miguel Martin
			template<typename Base>
			struct DeallocatorFunctor
			{
			public:
				
				static void destroy(Base* obj)
				{
					if(obj)
						delete obj;
				}
			};
		}
		
		/// A function that creates an object of type T, that is derived from class Base
		/// \return The created object
		template <typename Base, typename T>
		Base* create()
		{
			return util::AllocatorFunctor<Base, T>::create();
		}
		
		/// A function that destroys an object that is derived of class Base
		/// \param obj The object you wish to destroy
		template <typename Base>
		void destroy(Base* obj)
		{
			util::DeallocatorFunctor<Base>::destroy(obj);
		}
		
		
		/// \class ClassRegistry
		/// \brief A singleton that contains information about other classes
		///
		/// All other classes that are derived from Base is known in this class.
		/// A map of what their name is matched with the data to allocate/dealloc is stored in here
		///
		/// \author Miguel Martin
		template <typename Base>
		class ClassRegistry
		{
		public:
			
			static ClassRegistry<Base>& GetSharedInstance()
			{
				static ClassRegistry<Base> instance;
				return instance;
			}
			
			void add(const std::string& name, ClassRegistryData<Base>* data)
			{
				// insert it into the map
				_registeredClassData.insert(ClassRegistryDataDictionaryPair(name, data));
			}
			
			/// Gets ClassRegistryData resembled by the name of a class
			/// \param name The name of the class
			/// \return a null pointer if the class does not exsist, otherwise a pointer to the data
			/// that the class requires to create/destroy objects
			ClassRegistryData<Base>* get(const std::string& name)
			{
				// if the name doesn't exsist
				if(_registeredClassData.find(name) == _registeredClassData.end())
				{
					return NULL; // ...
				}
				
				// otherwise, give the caller the data he/she requires
				return _registeredClassData[name];
			}
			
		private:
			
			typedef std::pair<std::string, ClassRegistryData<Base>* > ClassRegistryDataDictionaryPair;
			typedef std::map<std::string, ClassRegistryData<Base>* > ClassRegistryDataDictionary;
			
			/// All the registered class data, mapped to a class's name
			ClassRegistryDataDictionary _registeredClassData;
		};
		
		///
		template <class Base, class T>
		class ClassRegistryEntry
		{
		public:
			
			static ClassRegistryEntry<Base, T>& GetSharedInstance(const std::string& name)
			{
				static ClassRegistryEntry<Base, T> instance(name);
				return instance;
			}
			
		private:
			
			ClassRegistryEntry(const std::string& name)
			: _data(create<Base, T>, destroy<Base>)
			{
				ClassRegistry<Base>::GetSharedInstance().add(name, &_data);
			}
			
			ClassRegistryData<Base> _data;
		};
		
	}
	
	/// Registers a class, with a custom name
	///
	/// \note
	/// It is reccomended to do this outside any namespaces, to avoid clutter in YOUR namespace(s) and also to
	/// ensure that the classtype name is entered with the namespaces it is in as a prefix.
	/// e.g.
	/// AC_CLASS_REGISTER(example::Base, example::Class)
	///
	/// \param base The base class
	/// \param classtype The class you wish to register
	/// \param classname The name you wish the class to have
#	define AC_CLASS_REGISTER_WITH_NAME(base, classtype, classname) 		\
namespace ac														\
{																	\
namespace object_factory											\
{																	\
namespace detail {													\
template<typename Base, typename T>									\
class ClassRegistration;											\
\
template<>															\
class ClassRegistration<base, classtype>							\
{																	\
static const ClassRegistryEntry<base, classtype>& entry;		\
};																	\
\
const																\
ClassRegistryEntry<base, classtype>&								\
ClassRegistration<base, classtype>::entry							\
= ClassRegistryEntry<base, classtype>::GetSharedInstance(classname);\
\
}																	\
}																	\
}
	
	/// Registers a class
	///
	/// \note
	/// It is reccomended to do this outside any namespaces, to avoid clutter in YOUR namespace(s) and also to
	/// ensure that the classtype name is entered with the namespaces it is in as a prefix.
	/// e.g.
	/// AC_CLASS_REGISTER(example::Base, example::Class)
	///
	/// \param base The base class
	/// \param classtype The class you wish to register
#	define AC_CLASS_REGISTER(base, classtype) AC_CLASS_REGISTER_WITH_NAME(base, classtype, #classtype)
	
	
	
	namespace object_factory
	{
		/// Creates an object
		/// \param name The name of the class in which you wish to create the object from
		/// \return The created object
		template<typename Base>
		Base* create(const std::string& name)
		{
			Base* obj = NULL;
			ClassRegistryData<Base>* data = ClassRegistry<Base>::GetSharedInstance().get(name);
			
			if(data)
			{
				// create the object
				obj = data->createFn();
			}
			
			return obj;
		}
	}
}

#endif // __AC_OBJECTFACTORY_H__