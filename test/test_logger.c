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
	logger.log(Logger::INFO, "info %d", Logger::INFO);
	logger.warn("warn");
	logger.error("error");
	logger.fatal("fatal %d", Logger::FATAL);

}