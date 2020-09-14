#include "logger.h"
#include "properties_config.h"

Logger::Logger(std::string cf): configFile(cf) {
	PropertiesConfig properties(configFile);
	 
	config.level = properties.getInt("log_level");
	config.logFile = properties.get("log_file");
	// new (this)Logger(conf);
	init();
}

Logger::Logger(LoggerConfig & conf): config(conf) {
	init();
}

Logger::Logger(int l) {
	config.level = l;
	init();
}


Logger::~Logger() {
	if(logFile != NULL) {
		if(fclose(logFile) != 0) {
			err_exit(errno, "Logger fclose");
		}
	}
	
}


void Logger::init() {
	logFile = NULL;
  if(!config.logFile.empty()) {
     logFile = fopen(config.logFile.c_str(), "a+");
     if(logFile == NULL) {
      err_msg(errno, "Logger fopen");
     }
  }
}

void Logger::log(int _level,  const char *fmt, ...) {

	if(_level < config.level)
		return;

	va_list		ap;
	va_start(ap, fmt);
	dolog(fmt, ap);
	va_end(ap);
}

void Logger::debug(const char *fmt, ...) {
	if(DEBUG < config.level)
		return;

	va_list		ap;
	va_start(ap, fmt);
	dolog(fmt, ap);
	va_end(ap);
}

void Logger::info(const char *fmt, ...) {
	if(INFO < config.level)
		return;

	va_list		ap;
	va_start(ap, fmt);
	dolog(fmt, ap);
	va_end(ap);
}

void Logger::warn(const char *fmt, ...) {
	if(WARN < config.level)
		return;

	va_list		ap;
	va_start(ap, fmt);
	dolog(fmt, ap);
	va_end(ap);
}

void Logger::error(const char *fmt, ...) {
	if(ERROR < config.level)
		return;

	va_list		ap;
	va_start(ap, fmt);
	dolog(fmt, ap);
	va_end(ap);
}

void Logger::fatal(const char *fmt, ...) {
	if(FATAL < config.level)
		return;
	va_list		ap;
	va_start(ap, fmt);
	dolog(fmt, ap);
	va_end(ap);
}