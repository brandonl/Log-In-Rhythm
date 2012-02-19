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

#ifndef __LOG_BASE_H__
#define __LOG_BASE_H__

#include <functional>
#include <string>
#include "LexicalCast.h"
#include "Uncopyable.h"

namespace rhythm
{
	namespace Log
	{
		/* If compiler supports c++11 strongly typed enums
		 *	VC10 is partial; translation it doesn't....
		 
		enum class Radix : unsigned char
		{
			bin = 2,
			oct = 8,
			dec = 10,
			hex = 16
		};
		*/
		enum Radix
		{
			bin = 2,
			oct = 8,
			dec = 10,
			hex = 16
		};

		enum Manip
		{
			tab = '\t',
			nl = '\n'
		};
	};


	// Interface to logging. Derived classes simply need to specify 
	// which device they write to through overriding of write(char)
	class LogBase : private Uncopyable
	{
	public:
		LogBase()
			:	radix(Log::dec)
		{}
		
		virtual ~LogBase(){}

 		LogBase& operator<< ( const Log::Radix r )
		{ 
			radix = r;
			return *this; 
		}

 		LogBase& operator<< ( const Log::Manip m )
		{ 
			write( static_cast<char>(m) );
			return *this; 
		}

		// Characters

 		LogBase& operator<< ( char c )
		{ 
			write( c );
			return *this; 
		}

 		LogBase& operator<< ( unsigned char c )
		{ 
			write( static_cast<char>(c) );
			return *this; 
		}

 		LogBase& operator<< ( char *str )
		{ 
			while( *str )
				write( *str++ );
			return *this; 
		}

		LogBase& operator<< ( const char * str )
		{ 
			while( *str )
				write( *str++ );
			return *this; 
		}

 		LogBase& operator<< ( unsigned char * str )
		{ 
			return operator<<( reinterpret_cast<char*>(str) );
		}

		LogBase& operator<< ( const unsigned char * str )
		{ 
			return operator<<( reinterpret_cast<const char*>(str) );
		}

		LogBase& operator<< ( const std::string &str )
		{
			return operator<<( str.c_str() );
		}

		// Numerics
 		LogBase& operator<< ( short val )
		{ 
			return operator<<( static_cast<long long>(val) ); 
		}

 		LogBase& operator<< ( unsigned short val )
		{ 
			return operator<<( static_cast<unsigned long long>(val) ); 
		}

 		LogBase& operator<< ( int val )
		{ 
			return operator<<( static_cast<long long>(val) ); 
		}

 		LogBase& operator<< ( unsigned val )
		{ 
			return operator<<( static_cast<unsigned long long>(val) ); 
		}

 		LogBase& operator<< ( long val )
		{ 
			return operator<<( static_cast<long long>(val) ); 
		}

 		LogBase& operator<< ( unsigned long val )
		{ 
			return operator<<( static_cast<unsigned long long>(val) ); 
		}

		LogBase& operator<< ( long long val )
		{
			val = (val < 0 && radix == 10 ) ? write('-'), -val : val;
			return operator<<( static_cast<unsigned long long>(val) ); 
		}

 		LogBase& operator<< ( unsigned long long val )
		{ 
			static const char *lookUp = "0123456789ABCDEF";

			unsigned long long largestBase = 1;
			while( val / largestBase >= static_cast<unsigned long long>(radix) )
				largestBase *= radix;

			switch(radix)
			{
				case 2:
					write('b');
					break;
				case 8:
					write('0');
					break;
				case 16:
					operator<<( "0x" );
					break;
				}

			while( largestBase )
			{
				write( lookUp[ val / largestBase ] );
				val %= largestBase;
				largestBase /= static_cast<unsigned long long>(radix);
			}
			return *this; 
		}

		LogBase& operator<< ( void* ptr )
		{
			Log::Radix prev = radix;
			radix = Log::hex;
			operator<<( reinterpret_cast<unsigned long long>(ptr) );
			radix = prev;
			return *this;
		}

		LogBase& operator<< ( float val )
		{ 
			return operator<<( static_cast< long double>(val) );
		}

		 LogBase& operator<< ( double val )
		{ 
			return operator<<( static_cast< long double>(val) );
		}

 		LogBase& operator<< ( long double val )
		{ 
			try
			{
				return operator<<( lexicalCast<std::string>(val) );
			}
			catch( std::bad_cast& e )
			{
				return operator<<( e.what() );
			}
		}
		
		LogBase& operator<< ( const std::function<const char*()> &stringtor )
		{
			return operator<<( stringtor() );
		}

	private:
		virtual void write( char c ){};

	private:
		Log::Radix radix;
	};
};

#endif