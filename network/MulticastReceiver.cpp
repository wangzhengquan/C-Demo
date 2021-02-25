#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), connect(), sendto(), and recvfrom() */
#include <arpa/inet.h>  /* for sockaddr_in and inet_addr() */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */
#include  "usg_common.h"
#define MAXRECVSTRING 255  /* Longest string to receive */


int main(int argc, char *argv[])
{
    int sock;                         /* Socket */
    struct sockaddr_in multicastAddr; /* Multicast Address */
    char *multicastIP;                /* IP Multicast Address */
    unsigned short multicastPort;     /* Port */
    char recvString[MAXRECVSTRING+1]; /* Buffer for received string */
    int recvStringLen;                /* Length of received string */
    struct ip_mreq multicastRequest;  /* Multicast address join structure */

    if (argc != 3)    /* Test for correct number of arguments */
    {
        fprintf(stderr,"Usage: %s <Multicast IP> <Multicast Port>\n", argv[0]);
        exit(1);
    }

    multicastIP = argv[1];        /* First arg: Multicast IP address (dotted quad) */
    multicastPort = atoi(argv[2]);/* Second arg: Multicast port */

    /* Create a best-effort datagram socket using UDP */
    if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
        err_exit(errno, "socket() failed");

    /* Construct bind structure */
    memset(&multicastAddr, 0, sizeof(multicastAddr));   /* Zero out structure */
    multicastAddr.sin_family = AF_INET;                 /* Internet address family */
    multicastAddr.sin_addr.s_addr = htonl(INADDR_ANY);  /* Any incoming interface */
    multicastAddr.sin_port = htons(multicastPort);      /* Multicast port */

    /* Bind to the multicast port */
    if (bind(sock, (struct sockaddr *) &multicastAddr, sizeof(multicastAddr)) < 0)
        err_exit(errno, "bind() failed");

    /* Specify the multicast group */
    multicastRequest.imr_multiaddr.s_addr = inet_addr(multicastIP);
    /* Accept multicast from any interface */
    multicastRequest.imr_interface.s_addr = htonl(INADDR_ANY);
    /* Join the multicast address */
    if (setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *) &multicastRequest,
          sizeof(multicastRequest)) < 0)
        err_exit(errno, "setsockopt() failed");

    for(;;) {
        /* Receive a single datagram from the server */
        if ((recvStringLen = recvfrom(sock, recvString, MAXRECVSTRING, 0, NULL, 0)) < 0)
            err_exit(errno, "recvfrom() failed");

        recvString[recvStringLen] = '\0';
        printf("Received: %s\n", recvString);    /* Print the received string */
    }
  
    
    close(sock);
    exit(0);
}
