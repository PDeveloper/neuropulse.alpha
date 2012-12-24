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

#ifndef __AC_ES_ES_H__
#define __AC_ES_ES_H__

/// \namespace ac
/// \brief A namespace that contains all the Anax Creations code
///
/// This namespace is the Anax Creations componany's namespace to avoid
/// any name collisions with any other pieces of code, in C/C++.
///
/// \author Miguel Martin
namespace ac
{
	/// \namespace es
	/// \brief A namespace that contains all classes/functions for the Anax Entity System
	///
	/// This namespace contains all you need to use the Anax Entity System.
	///
	/// \author Miguel Martin
	namespace es
	{
		
	}
}

/// \mainpage
///
/// \section welcome Welcome
///
/// Welcome to the Anax Entity System documentation, here you may find
/// detailed documentation on how to use specific classes/methods inside
/// the Anax Entity System.
///
/// \section resources Extra-resources
/// You may find more resources to learn about the Anax Entity System on
/// the Anax Entity System's wiki, hosted on BitBucket
/// <a href="https://bitbucket.org/miguelishawt/anax-entity-system/wiki/Home"> here</a>.

#define ANAX_ENTITY_SYSTEM_VERSION_MAJOR 0
#define ANAX_ENTITY_SYSTEM_VERSION_MINOR 2

#include "config.h"
#include "es/Scene.h"

// Entity Systems
#include "es/EntityProcessingSystem.h"

#endif // __AC_ES_ES_H__