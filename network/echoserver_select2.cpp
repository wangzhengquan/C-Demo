/*
 * echoservers.c - A concurrent echo server based on select
 */
/* $begin echoserversmain */
#include "usg_common.h"
#include "socket_io.h"

typedef struct { /* Represents a pool of connected descriptors */ //line:conc:echoservers:beginpool
  int maxfd;        /* Largest descriptor in read_set */
  fd_set read_set;  /* Set of all active descriptors */
  fd_set ready_set; /* Subset of descriptors ready for reading  */
  int nready;       /* Number of ready descriptors from select */
  int maxi;         /* Highwater index into client array */
  int clientfd[FD_SETSIZE];    /* Set of active descriptors */
  rio_t clientrio[FD_SETSIZE]; /* Set of active read buffers */
} pool; //line:conc:echoservers:endpool
/* $end echoserversmain */
void init_pool(int listenfd, pool *p);
void add_client(int connfd, pool *p);
void check_clients(pool *p);
/* $begin echoserversmain */

int byte_cnt = 0; /* Counts total bytes received by server */

int main(int argc, char **argv)
{
  int listenfd, connfd;
  socklen_t clientlen;
  struct sockaddr_storage clientaddr;
  static pool pool;

  char clienthost[NI_MAXHOST];
  char clientport[NI_MAXSERV];
  #define ADDRSTRLEN (NI_MAXHOST + NI_MAXSERV + 10)
  char addrStr[ADDRSTRLEN];

  if (argc != 2)
  {
    fprintf(stderr, "usage: %s <port>\n", argv[0]);
    exit(0);
  }
  listenfd = Open_listenfd(argv[1]);
  init_pool(listenfd, &pool); //line:conc:echoservers:initpool

  while (1)
  {
    /* Wait for listening/connected descriptor(s) to become ready */
    pool.ready_set = pool.read_set;
    pool.nready = select(pool.maxfd + 1, &pool.ready_set, NULL, NULL, NULL);

    /* If listening descriptor ready, add new client to pool */
    if (FD_ISSET(listenfd, &pool.ready_set))   //line:conc:echoservers:listenfdready
    {
      clientlen = sizeof(struct sockaddr_storage);
      connfd = accept(listenfd, (SA *)&clientaddr, &clientlen); 

      // print connection from
      if (getnameinfo((struct sockaddr *) &clientaddr, clientlen,
                  clienthost, NI_MAXHOST, clientport, NI_MAXSERV, 0) == 0)
          snprintf(addrStr, ADDRSTRLEN, "(%s:%s)", clienthost, clientport);
      else
          snprintf(addrStr, ADDRSTRLEN, "(?UNKNOWN?)");
      printf("Connection from %s\n", addrStr);

      add_client(connfd, &pool); //line:conc:echoservers:addclient
    }

    /* Echo a text line from each ready connected descriptor */
    check_clients(&pool); //line:conc:echoservers:checkclients
  }
}
/* $end echoserversmain */

/* $begin init_pool */
void init_pool(int listenfd, pool *p)
{
  /* Initially, there are no connected descriptors */
  int i;
  p->maxi = -1;                   //line:conc:echoservers:beginempty
  for (i = 0; i < FD_SETSIZE; i++)
    p->clientfd[i] = -1;        //line:conc:echoservers:endempty

  /* Initially, listenfd is only member of select read set */
  p->maxfd = listenfd;            //line:conc:echoservers:begininit
  FD_ZERO(&p->read_set);
  FD_SET(listenfd, &p->read_set); //line:conc:echoservers:endinit
}
/* $end init_pool */

/* $begin add_client */
void add_client(int connfd, pool *p)
{
  int i;
  p->nready--;
  for (i = 0; i < FD_SETSIZE; i++)  /* Find an available slot */
    if (p->clientfd[i] < 0)
    {
      /* Add connected descriptor to the pool */
      p->clientfd[i] = connfd;                 //line:conc:echoservers:beginaddclient
      Rio_readinitb(&p->clientrio[i], connfd); //line:conc:echoservers:endaddclient

      /* Add the descriptor to descriptor set */
      FD_SET(connfd, &p->read_set); //line:conc:echoservers:addconnfd

      /* Update max descriptor and pool highwater mark */
      if (connfd > p->maxfd) //line:conc:echoservers:beginmaxfd
        p->maxfd = connfd; //line:conc:echoservers:endmaxfd
      if (i > p->maxi)       //line:conc:echoservers:beginmaxi
        p->maxi = i;       //line:conc:echoservers:endmaxi
      break;
    }
  if (i == FD_SETSIZE) /* Couldn't find an empty slot */
    err_msg(0, "add_client error: Too many clients");
}
/* $end add_client */

/* $begin check_clients */
void check_clients(pool *p)
{
  int i, connfd, n;
  char buf[MAXLINE];
  rio_t rio;

  for (i = 0; (i <= p->maxi) && (p->nready > 0); i++)
  {
    connfd = p->clientfd[i];
    rio = p->clientrio[i];

    /* If the descriptor is ready, echo a text line from it */
    if ((connfd > 0) && (FD_ISSET(connfd, &p->ready_set)))
    {
      p->nready--;
      if ((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0)
      {
        byte_cnt += n; //line:conc:echoservers:beginecho
        printf("Server received %d (%d total) bytes on fd %d\n",
               n, byte_cnt, connfd);
        Rio_writen(connfd, buf, n); //line:conc:echoservers:endecho
      }

      /* EOF detected, remove descriptor from pool */
      else
      {
        Close(connfd); //line:conc:echoservers:closeconnfd
        FD_CLR(connfd, &p->read_set); //line:conc:echoservers:beginremove
        p->clientfd[i] = -1;          //line:conc:echoservers:endremove
      }
    }
  }
}
/* $end check_clients */
