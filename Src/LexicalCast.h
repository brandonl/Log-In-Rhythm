#ifndef LEXICAL_CAST_H__
#define LEXICAL_CAST_H__

#include <sstream>

template <class Tar, class Src>
Tar lexicalCast( Src arg )
{
	std::stringstream interpreter;
	Tar res;
	if( !(interpreter << arg) || !(interpreter >> res) || !(interpreter >> std::ws).eof() )
		throw std::bad_cast( "Bad Lexical Cast" );
	return res;
}

#endif