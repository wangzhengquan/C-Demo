/*
 * echoclient.c - An echo client
 */
/* $begin echoclientmain */
#include "usg_common.h"
#include "socket_io.h"

int main(int argc, char **argv)
{
  int clientfd;
  char *host, *port, buf[MAXLINE];
  rio_t rio;

  if (argc != 3)
  {
    fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
    exit(0);
  }
  host = argv[1];
  port = argv[2];

  clientfd = Open_clientfd(host, port);
  Rio_readinitb(&rio, clientfd);

  while (fgets(buf, MAXLINE, stdin) != NULL)
  {
    Rio_writen(clientfd, buf, strlen(buf));
    Rio_readlineb(&rio, buf, MAXLINE);
    fputs(buf, stdout);
  }
  Close(clientfd);
  exit(0);
}
/* $end echoclientmain */
