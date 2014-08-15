#pragma once
#define TRUTLE_HEADER

#include "../Trutle.h"

class Log
{
public:
	enum Level {
		VERBOSE,
		INFO,
		DEBUG,
		WARNING,
		ERROR,
	};

	static void 	SetLevel(Level level);

	static void 	Verbose(std::string format, ...);
	static void 	Info(std::string format, ...);
	static void 	Debug(std::string format, ...);
	static void 	Warning(std::string format, ...);
	static void 	Error(std::string format, ...);

private:
	static void 	Write(Level lvl, std::string format, va_list args);

	static Level 	sLoglevel;
};

#undef TRUTLE_HEADER
