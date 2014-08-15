#include "Log.h"


Log::Level Log::sLoglevel = Log::Level::VERBOSE;


/***** Static Public Methods *****/
void Log::SetLevel(Log::Level level)
{
	sLoglevel = level;
}

void Log::Verbose(std::string format, ...)
{
	va_list args;
	va_start(args, format);
	Write(VERBOSE, format.c_str(), args);
	va_end(args);
}

void Log::Info(std::string format, ...)
{
	va_list args;
	va_start(args, format);
	Write(INFO, "[INFO]: " + format, args);
	va_end(args);
}

void Log::Debug(std::string format, ...)
{
	va_list args;
	va_start(args, format);
	Write(DEBUG, "[DEBUG]: " + format, args);
	va_end(args);
}

void Log::Warning(std::string format, ...)
{
	va_list args;
	va_start(args, format);
	Write(WARNING, "[WARNING]: " +  WARNING, args);
	va_end(args);
}

void Log::Error(std::string format, ...)
{
	va_list args;
	va_start(args, format);
	Write(ERROR, "[ERROR]: " + format, args);
	va_end(args);
}


/***** Static Private Methods *****/
void Log::Write(Level lvl, std::string format, va_list args)
{
	if (lvl >= sLoglevel) {
		char *str = new char[format.length() * 3];
		vsprintf(str, format.c_str(), args);
		printf("%s", str);
		delete[] str;
	}
}
