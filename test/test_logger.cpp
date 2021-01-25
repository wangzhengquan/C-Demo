#include "usg_common.h"
#include "logger.h"
using namespace std;


void *run_recv(void *skptr) {
	pthread_detach(pthread_self());
	LoggerConfig config;
	config.level = Logger::DEBUG;
	config.logFile = "./1.log";
	config.console = 1;
	Logger logger(config);
  while(true) {
    logger.debug("================run_recv\n");
  }
}


int test1() {
	 
	 
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

int main() {
	pthread_t tid;
	pthread_create(&tid, NULL, run_recv, NULL);

	char action[512];
  while (true) {
    //printf("Usage: pub <topic> [content] or sub <topic>\n");
    printf("Can I help you? sub, pub, desub or quit\n");
    printf("client 1\n");
    scanf("%s", action);
  }
}