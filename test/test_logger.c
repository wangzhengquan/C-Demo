#include "usg_common.h"
#include "logger.h"
using namespace std;
int main() {
	// PropertiesConfig config("./config.txt");

	// std::cout << config.get("name") << std::endl;
	//Logger logger(Logger::WARN);
	Logger logger("./config.txt");
	logger.debug("debug");
	logger.log(Logger::INFO, "info %d", Logger::INFO);
	logger.warn("warn");
	logger.error("error");
	logger.fatal("fatal %d", Logger::FATAL);

}