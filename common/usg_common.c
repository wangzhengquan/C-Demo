#include "usg_common.h"
#include <errno.h> /* for definition of errno */


#ifdef _WIN32
#define PATH_SEPERATOR   "\\"
#else
#define PATH_SEPERATOR   "/"
#endif

static void err_doit(int, const char *, va_list);

/*void unix_error(const char *fmt, ...) */
/*{*/
/*va_list		ap;*/

/*va_start(ap, fmt);*/
/*err_doit(errno, fmt, ap);*/
/*va_end(ap);*/
/*}*/

void posix_error(int code, const char *fmt, ...) /* Posix-style error */
{
  va_list ap;

  va_start(ap, fmt);
  err_doit(code, fmt, ap);
  va_end(ap);
}

/*
 * Fatal error unrelated to a system call.
 * Error code passed as explict parameter.
 * Print a message and terminate.
 */
void err_exit(int error, const char *fmt, ...) {
  va_list ap;

  va_start(ap, fmt);
  err_doit(error, fmt, ap);
  va_end(ap);
  // abort();		/* dump core and terminate */
  exit(1);
}

/*
 * Nonfatal error unrelated to a system call.
 * Print a message and return.
 */
void err_msg(int error, const char *fmt, ...) {
  va_list ap;

  va_start(ap, fmt);
  err_doit(error, fmt, ap);
  va_end(ap);
}

/*
 * Print a message and return to caller.
 * Caller specifies "errnoflag".
 */
static void err_doit(int error, const char *fmt, va_list ap) {
  char buf[MAXLINE];
  vsnprintf(buf, MAXLINE - 1, fmt, ap);
  if (error != 0) {
    snprintf(buf + strlen(buf), MAXLINE - strlen(buf) - 1, ": %s", strerror(error));
  }
  strcat(buf, "\n");
  fflush(stdout);     /* in case stdout and stderr are the same */
  fputs(buf, stderr); // stderr
  fflush(NULL);       /* flushes all stdio output streams */
}

char *ltrim(char *str, const char *seps) {
  if(str == NULL) {
    return str;
  }
  size_t totrim;
  if (seps == NULL) {
    seps = "\t\n\v\f\r ";
  }
  totrim = strspn(str, seps);
  if (totrim > 0) {
    size_t len = strlen(str);
    if (totrim == len) {
      str[0] = '\0';
    } else {
      memmove(str, str + totrim, len + 1 - totrim);
    }
  }
  return str;
}

char *rtrim(char *str, const char *seps) {
  if(str == NULL) {
    return str;
  }
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

char *trim(char *str, const char *seps) {
  if(str == NULL) {
    return str;
  }
  return ltrim(rtrim(str, seps), seps);
}




/*
 * Join `dir` with `file`
 */
char * str_join( const char *seperator, const size_t n, char *first...) {
    size_t i, len, size = 1024;
    va_list vl;
    char *str, *buf;

    len = strlen(first);
    if(len >= size ) {
      size = len * 2;
    }
    buf = (char *)malloc(size);
    if (NULL == buf) return NULL;
    strcpy(buf, first);

    va_start(vl, first);
    i = 1;
    while(i < n) {
      str = va_arg(vl, char *);
      len += strlen(seperator);
      if(len >= size ) {
        size = len * 2;
        buf = (char *)realloc(buf, size);
      }
      strcat(buf,  seperator);
      len += strlen(str);
      if(len >= size ) {
        size = len * 2;
        buf = (char *)realloc(buf, size);
      }
      strcat(buf,  str);
      i++;
    }
    va_end(vl);
    buf[len] = '\0';
    return buf;
}


// char * str_join2(const char *arr[], const char *seperator) {

//   int size = 0, i = 0, c = 0;

//   while(1) {
//     if(arr[c] == NULL) {
//       break;
//     }
//     size += strlen(arr[c]);
//     c++;
//   }
//   char *buf = (char *)malloc(size + strlen(seperator) * (c-1) + 1);
//   if (NULL == buf) return NULL;

//   i = 0;
//   while(1) {
//     if(arr[i] == NULL) {
//       break;
//     }
//     if(i != 0) {
//       strcat(buf,  seperator);
//     }
//     strcat(buf,  arr[i]);
//     i++;
//   }

//   return buf;
 
// }



char * path_join(const size_t n, char *path, ...) {
  size_t i, spn, len, size = 1024;
  va_list vl;
  char *str;
  len = strlen(path);
  if(len >= size ) {
    size = len * 2;
  }
  char *buf = (char *)malloc(size);
  if (NULL == buf) return NULL;
  strcpy(buf, path);

  va_start(vl, path);
  i = 1;
  while(i < n) {
    str = va_arg(vl, char *);

    if(strcmp(buf+len-strlen(PATH_SEPERATOR), PATH_SEPERATOR) == 0) {
      len -= strlen(PATH_SEPERATOR);
      *(buf+len) = '\0';
    }
   
    if( (spn = strspn(str, PATH_SEPERATOR)) > 0 ) {
      str = str + spn;
    }

    len += strlen(PATH_SEPERATOR);
    if(len >= size ) {
      size = len * 2;
      buf = (char *)realloc(buf, size);
    }
    strcat(buf,  PATH_SEPERATOR);

    len += strlen(str);
    if(len >= size ) {
      size = len * 2;
      buf = (char *)realloc(buf, size);
    }
    strcat(buf,  str);
    i++;
  }
  va_end(vl);
  buf[len] = '\0';
  return buf;
}

