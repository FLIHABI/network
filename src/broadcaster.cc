/*
** broadcaster.c -- a datagram "client"
**                  this one can broadcast
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "network.hh"
#include "broadcaster.hh"

int broadcastLoop()
{
    while (1)
    {
        broadcast(BROADCAST_ADD, BROADCAST_MSG, BROADCAST_PORT);
        sleep(5);
    }
    return 0;
}

int broadcast(const char *ip, const char *msg, int port)
{
    int sockfd;
    struct sockaddr_in their_addr; // connector's address information
    struct hostent *he;
    int numbytes;
    int broadcast = 1;
    //char broadcast = '1'; // if that doesn't work, try this

    if ((he=gethostbyname(ip)) == NULL) {  // get the host info
        perror("Broadcaster: gethostbyname");
        exit(1);
    }

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("Broadcaster: socket");
        exit(1);
    }

    // this call is what allows broadcast packets to be sent:
    if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast,
        sizeof broadcast) == -1) {
        perror("Broadcaster: setsockopt (SO_BROADCAST)");
        exit(1);
    }

    their_addr.sin_family = AF_INET;     // host byte order
    their_addr.sin_port = htons(port); // short, network byte order
    their_addr.sin_addr = *((struct in_addr *)he->h_addr);
    memset(their_addr.sin_zero, '\0', sizeof their_addr.sin_zero);

    if ((numbytes=sendto(sockfd, msg, strlen(msg), 0,
             (struct sockaddr *)&their_addr, sizeof their_addr)) == -1) {
        perror("Broadcaster: sendto");
        exit(1);
    }

    printf("Broadcaster: sent %d bytes to %s\n", numbytes,
        inet_ntoa(their_addr.sin_addr));

    close(sockfd);

    return 0;
}
