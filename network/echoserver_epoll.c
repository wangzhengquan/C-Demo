/* include fig01 */
#include  "usg_common.h"
#include "socket_io.h"
#include <fcntl.h>
#include <sys/epoll.h>


#define OPEN_MAX 1024
#define MAX_EVENTS     5 
int
main(int argc, char **argv)
{
  int      epfd,  i, listenfd, connfd;

  socklen_t clientlen;
  struct sockaddr_storage clientaddr;
  
  int         nready;
  ssize_t       n;
  char        buf[MAXLINE];

  char clienthost[NI_MAXHOST];
  char clientport[NI_MAXSERV];
  #define ADDRSTRLEN (NI_MAXHOST + NI_MAXSERV + 10)
  char addrStr[ADDRSTRLEN];

  struct epoll_event ev;
  struct epoll_event evlist[MAX_EVENTS];

  if (argc != 2)
  {
    fprintf(stderr, "usage: %s <port>\n", argv[0]);
    exit(0);
  }

  epfd = epoll_create(OPEN_MAX);

  listenfd = Open_listenfd(argv[1]);;

  ev.events = EPOLLIN;            /* Only interested in input events */
  ev.data.fd = listenfd;
  if (epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev) == -1)
      err_exit(errno, "epoll_ctl");
 

  for ( ; ; )
  {
    nready = epoll_wait(epfd, evlist, MAX_EVENTS, -1);
    if (nready == -1) {
      if (errno == EINTR)
        continue;               /* Restart if interrupted by signal */
      else
        err_exit(errno, "epoll_wait");
    }

    printf("Ready: %d\n", nready);

    for (i = 0; i < nready; i++)
    {
      printf("  fd=%d; events: %s%s%s\n", evlist[i].data.fd,
             (evlist[i].events & EPOLLIN)  ? "EPOLLIN "  : "",
             (evlist[i].events & EPOLLHUP) ? "EPOLLHUP " : "",
             (evlist[i].events & EPOLLERR) ? "EPOLLERR " : "");

      if (evlist[i].events & EPOLLIN)
      {

        if(evlist[i].data.fd == listenfd) {
          
          clientlen = sizeof(struct sockaddr_storage);
          connfd = accept(listenfd, (SA *)&clientaddr, &clientlen); 

          if (getnameinfo((struct sockaddr *) &clientaddr, clientlen,
                  clienthost, NI_MAXHOST, clientport, NI_MAXSERV, 0) == 0)
              snprintf(addrStr, ADDRSTRLEN, "(%s:%s)", clienthost, clientport);
          else
              snprintf(addrStr, ADDRSTRLEN, "(?UNKNOWN?)");
          printf("Connection from %s\n", addrStr);

          ev.events = EPOLLIN;            /* Only interested in input events */
          ev.data.fd = connfd;
          if (epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &ev) == -1)
              err_exit(errno, "epoll_ctl");

        } else {
          connfd = evlist[i].data.fd;
          if ( (n = read(connfd, buf, MAXLINE)) < 0) {
            if (errno == ECONNRESET) {
              /*connection reset by client */
              printf("client[%d] aborted connection\n", i);
              close(connfd);
              // Closing a file descriptor automatically removes it from all of the epoll interest lists of which it is a member.
              if (epoll_ctl(epfd, EPOLL_CTL_DEL, connfd, NULL) == -1)
                err_msg(errno, "epoll_ctl EPOLL_CTL_DEL");
            }
            else
              err_msg( errno, "read error");
          }
          else if (n == 0)
          {
            /*4connection closed by client */
            printf("client[%d] closed connection\n", i);
            close(connfd);
            // Closing a file descriptor automatically removes it from all of the epoll interest lists of which it is a member.
            if (epoll_ctl(epfd, EPOLL_CTL_DEL, connfd, NULL) == -1)
              err_msg(errno, "epoll_ctl EPOLL_CTL_DEL");
          }
          else
            rio_writen(connfd, buf, n);

        }
      }
      else if (evlist[i].events & (EPOLLHUP | EPOLLERR))
      {

        /* After the epoll_wait(), EPOLLIN and EPOLLHUP may both have
           been set. But we'll only get here, and thus close the file
           descriptor, if EPOLLIN was not set. This ensures that all
           outstanding input (possibly more than MAXLINE bytes) is
           consumed (by further loop iterations) before the file
           descriptor is closed. */
        connfd = evlist[i].data.fd;
        printf("    closing fd %d\n", connfd);
        if (close(connfd) == -1)
          err_exit(errno, "close");
      }
    }
  }
}
/* end fig02 */
