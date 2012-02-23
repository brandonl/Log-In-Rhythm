Log In Rhythm or Rhythm (as it's namespace suggests) is a customizable logging system for C++ applications.


Log In Rhythm gives you the ability to write messages in a type safe manner- errors, reports, warnings, etc...- to your desired output device.
Similar to usage of iostreams.

Basic usage:

```
#include "Rhythm.hpp"

...
using namespace rhythm;

rlog << Log::Warn() << "Shader::Load: Failed to open geometry shader; file: " << fp << Log::nl;
...
```

You can create your own warning levels with the following:
```
#include "StdLevels.hpp"

namespace Log
{

class MyLevel : public Level
{
	const char * operator()()
	{
		return "[ MY WARNING ] ";
	}
};

};
...
rlog << Log::MyLevel() << "Message" << Log::nl;
```

By using Rhythm you can easily turn off all reporting by simply switching to release profile in VC or
defining NDEBUG.

Doing so will remove any trace of rhythm and have 0 run time impact.

Along the same lines you can selectively disable certain warning levels through the macro provided in "Rhythm.hpp" header.
```
DISABLE_LEVEL( Warn )
```

Will remove and messages with the level Warn specified.

The provided output devices are ConsoleLog( stdout), FileLog( filebuff ), and WebLog.

Notably WebLog writes messages as with html tags to an html file in /Log/.
This file links a style sheet that allows you to read errors in your own custom css style.
Also provided a javascript file that auto refreshes the html file every x seconds for convience.