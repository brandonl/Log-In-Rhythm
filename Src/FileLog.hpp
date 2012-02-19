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

	Brandon Luth
	brandonluth@gmail.com
 */

#ifndef __FILE_LOG_H__
#define __FILE_LOG_H__

#include "LogBase.hpp"
#include <fstream>

namespace rhythm
{
	class FileLog : public LogBase
	{
	public:
		FileLog() : LogBase()
		{
			buff.open( "RhythmLog.txt", std::ios::out | std::ios::app );
		}

		~FileLog()
		{
			buff.close();
		}
	private:
		virtual void write( char c )
		{
			buff.sputc(c);
		}

		std::filebuf buff;
	};
};

#endif