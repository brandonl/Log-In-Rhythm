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

#include "Rhythm.hpp"
#include <iostream>

/* NOTE: User defined literals for stream manipulation 
 *	if compiler supports

unsigned operator"" w( unsigned fieldWidth )
{
	return fieldWidth;
}
*/

#include <string>
#include <iomanip>

DISABLE_LEVEL( Report )

int main()
{
	using namespace rhythm;
	using std::cin;

	rlog << &Logger::activeStream() << Log::nl;
	// Notice this line does nothing since the log was default inited with a 
	// console and that default Log is created as a singleton
	// THus the address below is the same as above.
	Logger::setStream<ConsoleLog>();
	rlog << &Logger::activeStream() << Log::nl;

	std::string s = "String: I am it\n";
	rlog << s.c_str();
	rlog << bool(1) << " <TRUE FALSE> " << bool(0) << Log::nl;
	rlog << "Hello" << Log::tab << "World" << Log::nl<< Log::nl;

	int x = 1;
	rlog << "Address: "<<  &x << "\nDouble: " << 1.103 << "\nFloat: " << 1.105f << "Long Double: " << 1.1055l << Log::nl<< Log::nl;

	short sss = 1;
	unsigned short us = 1;
	wchar_t ws = L'c';
	rlog << "What follows: 111..111 in dec x 2, bin 4096, dec int, unisgned, long,\n unsigned long, long long, unsigned long long, short, unsigned short, wide char" << Log::nl;
	rlog << Log::nl << Log::dec << unsigned long long(~0);
	rlog << Log::nl << Log::dec << ~0;
	rlog << Log::nl << Log::bin << 4096;
	rlog << Log::nl << Log::dec << 1 << 1u << 1l << 1ul << 1ll << 1ull << sss << us << ws;
	

	// Test level
	rlog << Log::nl;
	rlog << Log::Warn() << "I'm Warning you.\n";
	// Due to MACRO up top Info has been disabled from logging.
	rlog << Log::Report() << "I'm Informative.\n";

	// Switch to FileLog whcih was generated as static var so already exists
	Logger::setStream<WebLog>();
	//rlog << "FILE ADDR " << &Logger::activeStream() << Log::nl;

	rlog << Log::Warn() << __FILE__ << " " << __LINE__ << Log::nl;
	rlog << Log::Error() << "gjriegjt" << Log::nl;
	rlog << "jgreijgier" << Log::nl;
	char c;
	std::cin >> c;

	return 0;
};