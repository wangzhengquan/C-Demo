/*
 * Our own header, to be included before all standard system headers.
 */

#ifndef __USG_COMMON_H__
#define __USG_COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <setjmp.h>
#include <signal.h>
#include <dirent.h>
#include <time.h>
#include <sched.h>

#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <errno.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
/*
define int8_t uint8_t int16_t uint16_t int32_t uint32_t int64_t uint64_t
*/
#include <stdint.h>



//c++ header

#include <iostream>
#include <string>
#include <cstdlib>
#include <atomic>



/* Our own error-handling functions */

void err_exit(int error, const char *fmt, ...);
void err_msg(int error, const char *fmt, ...);

static inline int 
itoa(int num, char *str) 
{
	 return sprintf(str, "%d", num); 

}

static inline int 
ftoa(float num, char *str) 
{
	 return sprintf(str, "%f", num); 

}
#endif
