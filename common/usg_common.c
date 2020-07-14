#include "usg_common.h"
#include <errno.h>		/* for definition of errno */

#define MAXLINE 4096      /* max line length */
/**************************
 * Error-handling functions
 **************************/

static void	err_doit(int, const char *, va_list);

 
/*void unix_error(const char *fmt, ...) */
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
	//abort();		/* dump core and terminate */
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
	if (error != 0) {
		snprintf(buf+strlen(buf), MAXLINE-strlen(buf)-1, ": %s", strerror(error));
	}
	strcat(buf, "\n");
	fflush(stdout);		/* in case stdout and stderr are the same */
	fputs(buf, stderr); //stderr
	fflush(NULL);		/* flushes all stdio output streams */
}

char *ltrim(char *str, const char *seps)
{
    size_t totrim;
    if (seps == NULL) {
        seps = "\t\n\v\f\r ";
    }
    totrim = strspn(str, seps);
    if (totrim > 0) {
        size_t len = strlen(str);
        if (totrim == len) {
            str[0] = '\0';
        }
        else {
            memmove(str, str + totrim, len + 1 - totrim);
        }
    }
    return str;
}

char *rtrim(char *str, const char *seps)
{
    int i;
    if (seps == NULL) {
        seps = "\t\n\v\f\r ";
    }
    i = strlen(str) - 1;
    while (i >= 0 && strchr(seps, str[i]) != NULL) {
        str[i] = '\0';
        i--;
    }
    return str;
}

char *trim(char *str, const char *seps)
{
    return ltrim(rtrim(str, seps), seps);
}