#include "usg_common.h"
#include "logger.h"
using namespace std;
int main() {
	 
	 
	// LoggerConfig config;
	// config.level = 3;
	// config.logFile = "./1.log";
	// Logger logger(config);
	Logger logger("config.txt");
	logger.debug("debug");
	logger.log(Logger::INFO, "info %d\n", Logger::INFO);
	logger.warn("warn %d\n", 123);
	logger.error("error %d\n", 123);
	logger.fatal("fatal %d\n", Logger::FATAL);

}