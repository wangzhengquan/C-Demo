#include "logger.h"
#include "properties_config.h"

Logger::Logger(std::string cf): configFile(cf) {
	PropertiesConfig config(configFile);
	level = config.getInt("log_level");
}

void Logger::log(int _level,  const char *fmt, ...) {

	if(_level < level)
		return;

	va_list		ap;
	va_start(ap, fmt);
	dolog(fmt, ap);
	va_end(ap);
}


void Logger::debug(const char *fmt, ...) {
	if(DEBUG < level)
		return;

	va_list		ap;
	va_start(ap, fmt);
	dolog(fmt, ap);
	va_end(ap);
}

void Logger::info(const char *fmt, ...) {
	if(INFO < level)
		return;

	va_list		ap;
	va_start(ap, fmt);
	dolog(fmt, ap);
	va_end(ap);
}

void Logger::warn(const char *fmt, ...) {
	if(WARN < level)
		return;

	va_list		ap;
	va_start(ap, fmt);
	dolog(fmt, ap);
	va_end(ap);
}

void Logger::error(const char *fmt, ...) {
	if(ERROR < level)
		return;

	va_list		ap;
	va_start(ap, fmt);
	dolog(fmt, ap);
	va_end(ap);
}

void Logger::fatal(const char *fmt, ...) {
	if(FATAL < level)
		return;
	va_list		ap;
	va_start(ap, fmt);
	dolog(fmt, ap);
	va_end(ap);
}