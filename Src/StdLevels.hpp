#ifndef __STD_LEVELS_H__
#define __STD_LEVELS_H__

namespace rhythm
{
	namespace Log
	{
		struct Level
		{
			virtual const char* operator()() = 0;
		};

		struct Warn : public Level
		{
			virtual const char* operator()()
			{
				return "[ WARNING ] ";
			}
		};

		struct Report : public Level
		{
			virtual const char* operator()()
			{
				return "[ REPORT ] ";
			}
		};

		struct Error : public Level
		{
			virtual const char* operator()()
			{
				return "[ ERROR ] ";
			}
		};
	};
};

#endif