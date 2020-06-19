#include "usg_common.h"

int main(void)
{
  int fd;
  char line[100];
  int n;
  fd = open("./hello.txt", O_RDONLY);
  sleep(10);
  while((n = read(fd, line, 100)) > 0) {
    write(1, line, n);
  } 
  exit(0);
}
