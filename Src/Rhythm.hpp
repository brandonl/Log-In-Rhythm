/*
	Log In Rhythm (Rhythm)
   Copyright (C) 2012 Brandon Luth

   This software is provided 'as-is', without any express or implied
   warranty. In no event will the authors be held liable for any
   damages arising from the use of this software.

   Permission is granted to anyone to use this software for any
   purpose, including commercial applications, and to alter it and
   redistribute it freely, subject to the following restrictions:

   1. The origin of this software must not be misrepresented; you
      must not claim that you wrote the original software. If you use
      this software in a product, an acknowledgment in the product
      documentation would be appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and
      must not be misrepresented as being the original software.

   3. This notice may not be removed or altered from any source
      distribution.

	Source based on Michael Schulze <mschulze@ivs.cs.uni-magdeburg.de> Logger
	Described at DrDobbs.com

	Brandon Luth
	brandonluth@gmail.com
 */

#ifndef __LOG_IN_RHYTHM_H__
#define __LOG_IN_RHYTHM_H__

#include "ConsoleLog.hpp"
#include "WebLog.hpp"
#include "DevNull.hpp"
#include "FileLog.hpp"
#include "Logger.hpp"
#include "StdLevels.hpp"

// TODO: Change to a first time switch 
#define rlog Log::write()


#define DISABLE_LEVEL( LEVEL )										\
namespace rhythm															\
{																				\
inline DevNull& operator<< ( LogBase& lb, Log::LEVEL& )		\
{																				\
	return *reinterpret_cast<DevNull*>(0x0);						\
}																				\
};


namespace rhythm
{
	namespace Log
	{
#ifdef NDEBUG
		// Let the preprocessor select wether we will have any impact on the 
		// program what-so-ever..
		inline DevNull& write()
		{
			return *reinterpret_cast<DevNull*>(0x0);
		}

#else

		inline LogBase& write()
		{
			Logger::printPreCondition();
			return Logger::activeStream();
		}

#endif	
	};
};

#endif