#include "Log.h"


Log::Level Log::sLoglevel = Log::Level::VERBOSE;


/***** Static Public Methods *****/
void Log::SetLevel(Log::Level level) {
	sLoglevel = level;
}

void Log::Verbose(std::string str) {
	Write("[VERBOSE]: " + str, VERBOSE);
}

void Log::Info(std::string str) {
	Write("[INFO]: " + str, INFO);
}

void Log::Debug(std::string str) {
	Write("[DEBUG]: " + str, DEBUG);
}

void Log::Warning(std::string str) {
	Write("[WARNING]: " + str, WARNING);
}

void Log::Error(std::string str) {
	Write("[ERROR]: " + str, ERROR);
}


/***** Static Private Methods *****/
void Log::Write(std::string str, Level lvl) {
	if (lvl >= sLoglevel) {
		printf("%s\n", str.c_str());		
	}
}