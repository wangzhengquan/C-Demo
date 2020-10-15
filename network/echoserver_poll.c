/* include fig01 */
#include  "usg_common.h"
#include "socket_io.h"
#include <poll.h>


#define OPEN_MAX 1024

int
main(int argc, char **argv)
{
  int         i, maxi, listenfd, connfd, sockfd;
  int         nready;
  ssize_t       n;
  char        buf[MAXLINE];
  socklen_t     clilen;
  struct pollfd   client[OPEN_MAX];
  struct sockaddr_in  cliaddr, servaddr;
  int port;

  if (argc != 2)
  {
    fprintf(stderr, "usage: %s <port>\n", argv[0]);
    exit(0);
  }

  port = atoi(argv[1]);

  listenfd = socket(AF_INET, SOCK_STREAM, 0);

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family      = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port        = htons(port);

  bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

  listen(listenfd, LISTENQ);

  client[0].fd = listenfd;
  client[0].events = POLLRDNORM;
  for (i = 1; i < OPEN_MAX; i++)
    client[i].fd = -1;    /* -1 indicates available entry */
  maxi = 0;         /* max index into client[] array */
  /* end fig01 */

  /* include fig02 */
  for ( ; ; )
  {
    nready = poll(client, maxi + 1, -1);

    if (client[0].revents & POLLRDNORM)   /* new client connection */
    {
      clilen = sizeof(cliaddr);
      connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);
#ifdef  NOTDEF
      printf("new client: %s\n", sock_ntop((struct sockaddr *) &cliaddr, clilen));
#endif

      for (i = 1; i < OPEN_MAX; i++)
        if (client[i].fd < 0)
        {
          client[i].fd = connfd;  /* save descriptor */
          break;
        }
      if (i == OPEN_MAX)
        err_exit(0, "too many clients");

      client[i].events = POLLRDNORM;
      if (i > maxi)
        maxi = i;       /* max index in client[] array */

      if (--nready <= 0)
        continue;       /* no more readable descriptors */
    }

    for (i = 1; i <= maxi; i++)   /* check all clients for data */
    {
      if ( (sockfd = client[i].fd) < 0)
        continue;
      if (client[i].revents & (POLLRDNORM | POLLERR))
      {
        if ( (n = read(sockfd, buf, MAXLINE)) < 0)
        {
          if (errno == ECONNRESET)
          {
            /*4connection reset by client */
#ifdef  NOTDEF
            printf("client[%d] aborted connection\n", i);
#endif
            close(sockfd);
            client[i].fd = -1;
          }
          else
            err_msg(errno, "read error");

        }
        else if (n == 0)
        {
          /*4connection closed by client */
#ifdef  NOTDEF
          printf("client[%d] closed connection\n", i);
#endif
          close(sockfd);
          client[i].fd = -1;
        }
        else
          rio_writen(sockfd, buf, n);

        if (--nready <= 0)
          break;        /* no more readable descriptors */
      }
    }
  }
}
/* end fig02 */
