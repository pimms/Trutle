#pragma once
#define TRUTLE_HEADER

#include "../Trutle.h"

class Log {
public:
	enum Level {
		VERBOSE,
		INFO,
		DEBUG,
		WARNING,
		ERROR,
	};

	static void 	SetLevel(Level level);

	static void 	Verbose(std::string str);
	static void 	Info(std::string str);
	static void 	Debug(std::string str);
	static void 	Warning(std::string str);
	static void 	Error(std::string str);

private:
	static void 	Write(std::string str, Level lvl);

	static Level 	sLoglevel;
};

#undef TRUTLE_HEADER