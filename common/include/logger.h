#ifndef __LOGGER_H__
#define __LOGGER_H__

#include "usg_common.h"
#include "usg_typedef.h"

class Logger {
	std::string configFile;
	int level;

	void dolog(const char *fmt, va_list ap)
	{
		char	buf[MAXBUF];
		vsnprintf(buf, MAXBUF-1, fmt, ap);
		strcat(buf, "\n");
		fflush(stdout);		/* in case stdout and stderr are the same */
		fputs(buf, stderr);
		fflush(NULL);		/* flushes all stdio output streams */
	}
public:
	enum {
		ALL ,
		DEBUG ,
		INFO ,
		WARN ,
		ERROR ,
		FATAL ,
		OFF
	};

	Logger(int l = INFO): level(l) {}
	Logger(std::string cf);
	

	void log(int _level,  const char *fmt,  ...);

	void debug(const char *fmt, ...);
	void info(const char *fmt, ...);
	void warn(const char *fmt, ...);
	void error(const char *fmt, ...);
	void fatal(const char *fmt, ...);
};

#endif