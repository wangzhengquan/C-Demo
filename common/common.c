#include "common.h"
#include <errno.h>		/* for definition of errno */
#include <stdarg.h>		/* ISO C variable aruments */

/**************************
 * Error-handling functions
 **************************/
static void	err_doit(int, const char *, va_list);
//static void err_doit(int errno, const char *fmt, va_list ap);

/*void unix_error(const char *fmt, ...) [> Unix-style error <]*/
/*{*/
	/*va_list		ap;*/

	/*va_start(ap, fmt);*/
	/*err_doit(errno, fmt, ap);*/
	/*va_end(ap);*/
/*}*/

void posix_error(int code, const char *fmt, ...) /* Posix-style error */
{
	va_list		ap;

	va_start(ap, fmt);
	err_doit(code, fmt, ap);
	va_end(ap);
}

/*
 * Fatal error unrelated to a system call.
 * Error code passed as explict parameter.
 * Print a message and terminate.
 */
void err_exit(int error, const char *fmt, ...)
{
	va_list		ap;

	va_start(ap, fmt);
	err_doit(error, fmt, ap);
	va_end(ap);
	abort();		/* dump core and terminate */
	exit(1);
}


/*
 * Nonfatal error unrelated to a system call.
 * Print a message and return.
 */
void err_msg(int error, const char *fmt, ...)
{
	va_list		ap;

	va_start(ap, fmt);
	err_doit(error, fmt, ap);
	va_end(ap);
}


/*
 * Print a message and return to caller.
 * Caller specifies "errnoflag".
 */
static void err_doit(int error, const char *fmt, va_list ap)
{
	char	buf[MAXLINE];

	vsnprintf(buf, MAXLINE-1, fmt, ap);
	snprintf(buf+strlen(buf), MAXLINE-strlen(buf)-1, ": %s", strerror(error));
	strcat(buf, "\n");
	fflush(stdout);		/* in case stdout and stderr are the same */
	fputs(buf, stderr);
	fflush(NULL);		/* flushes all stdio output streams */
}
