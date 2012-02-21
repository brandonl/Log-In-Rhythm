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

#ifndef __WEB_LOG_H__
#define __WEB_LOG_H__

#include "LogBase.hpp"
#include <fstream>
#include <string>

namespace rhythm
{
	class WebLog : public LogBase
	{
	public:
		WebLog() : LogBase()
		{
			file.open(  "./Log/RhythmWebLog.html", std::fstream::out | std::fstream::in );
			file.seekp( 0, std::ios::end );
			if( !file.tellp() )
				file << prepare();
		}

		~WebLog()
		{
		}

		void preCond()
		{
			LogBase::operator<<( "<div class=\"entry\">\n");
		}

		//Override inorder to end entry.
		//This means every web log entry must be ended with the correct manip
 		LogBase& operator<< ( const Log::Manip m )
		{ 
			write( static_cast<char>(m) );
			LogBase::operator<<( "</div>\n" );
			file.flush();
			return *this; 
		}

		//Override functor/lambda in order to know what warnign is being printed..
		LogBase& operator<< ( Log::Level &l )
		{
			std::string lstr = l();
			std::string bhtml = "", ehtml = "\n";
			if( lstr == "[ WARNING ] " )
			{
				bhtml = "<h1 class=\"warn\">";
				ehtml = "</h1>\n";
			}
			else if( lstr == "[ ERROR ] " )
			{
				bhtml = "<h1 class=\"error\">";
				ehtml = "</h1>\n";
			}

			return LogBase::operator<<( bhtml + l() + ehtml );
		}

	private: 
		const char* prepare()
		{
			return"<html>\n"
					"<head>\n"
					"<title>Rhythm Log</title>\n"
					"<link href=\"http://fonts.googleapis.com/css?family=Droid+Sans+Mono&amp;v1\" rel=\"stylesheet\" type=\"text/css\">\n"
					"<link rel=\"stylesheet\" type=\"text/css\" media=\"screen\" href=\"./css/style.css\">\n"
					"</head>\n"
					"<body>\n";
		}

		virtual void write( char c )
		{
			file.put(c);
		}

		std::fstream file;
	};
};

#endif