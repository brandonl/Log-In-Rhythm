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

		struct Info : public Level
		{
			virtual const char* operator()()
			{
				return "[ INFO ] ";
			}
		};

		struct Error : public Level
		{
			virtual const char* operator()()
			{
				return "[ Error ] ";
			}
		};
	};
};

#endif