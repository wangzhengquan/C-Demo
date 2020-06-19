#include "usg_common.h"

int main(void)
{
  int   n, i;
  int   fd[2], fd2[2];
  pid_t pid;
  char  line[MAXLINE];

  if (pipe(fd) < 0)
    err_exit(errno, "pipe error");
  if (pipe(fd2) < 0)
    err_exit(errno, "pipe error");

  if ((pid = fork()) < 0)
  {
    err_exit(errno, "fork error");
  }
  else if (pid > 0)       /* parent */
  {
    close(fd[0]);
    close(fd2[1]);
    while ((n = read(STDIN_FILENO, line, MAXLINE)) > 0)
    {
      write(fd[1], line, n);
      n = read(fd2[0], line, MAXLINE);
      write(STDOUT_FILENO, line, n);
    }
  }
  else              /* child */
  {
    close(fd[1]);
    close(fd2[0]);
    while ((n = read(fd[0], line, MAXLINE)) > 0)
    {
      for (i = 0; i < n; i++)
      {
        line[i] = toupper(line[i]);
      }
      write(fd2[1], line, n);
    }
  }
  exit(0);
}
