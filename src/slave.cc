/*
 * ============================================================================
 *       Filename:  slave.hxx
 *    Description:  Slave side implementation for flihabi network
 *        Version:  1.0
 *        Created:  04/26/2015 02:40:40 AM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  Rafael Gozlan, rafael.gozlan@epita.fr
 *   Organization:  Flihabi
 * ============================================================================
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
#include <iostream>
#include <string>

#include "utils.hh"
#include "network.hh"
#include "slave.hh"
#include "listener.hh"

// PUBLIC METHODS

Slave::Slave()
{
    std::string ip = getServerAddress();
    connectToServer(ip, CONNECTION_PORT);
}

std::string Slave::getBytecode()
{
    ssize_t nbytes;
    uint64_t len;
    if ((len = Utils::recvBytecodeLen(sockfd_)) == (uint64_t) -1)
    {
        perror("Slave: failed to recv bytecode len");
        return "";
    }
    char *buf = (char*) malloc(len);
    memset(buf, 0, len);
    std::cout << "Slave: Waiting for " << len << " bytes" << std::endl;
    char *aux = buf;
    // Receiving connection msg
    while (len > 0)
    {
        if (len < 4096)
            nbytes = recv(sockfd_, aux, len, 0);
        else
            nbytes = recv(sockfd_, aux, 4096, 0);
        len -= nbytes;
        aux += nbytes;

    }
    for (uint64_t i = 0; i < len; i++)
    {
        if (buf[i] <= '~' && buf[i] >= ' ')
            printf("%c", buf[i]);
        else
            printf("\\%02X", buf[i]);
    }
    printf("\n");

    return std::string(buf, len);
}

int Slave::send_bytecode(std::string bytecode)
{
    if (Utils::sendBytecode(sockfd_, bytecode, bytecode.size()) == (uint64_t)-1)
    {
        perror("Client thread: failed sending bytecode");
        return -1;
    }
    return 0;
}

// PRIVATE METHODS

std::string Slave::getServerAddress()
{
    Socket *s = listen(BROADCAST_PORT);
    close(s->sockfd);
    return s->ip;
}

void Slave::connectToServer(std::string ip, int port)
{
    int sockfd, numbytes;
    char buf[100];
    struct addrinfo hints, *servinfo, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    std::cout << "Trying to connect to " << ip << " " << port << std::endl;

    if ((rv = getaddrinfo(ip.c_str(), std::to_string(port).c_str(), &hints, &servinfo)) != 0)
    {
        fprintf(stderr, "Slave: getaddrinfo: %s\n", gai_strerror(rv));
        return;
    }

    // loop through all the results and connect to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                        p->ai_protocol)) == -1) {
            perror("Slave: failed to get socket");
            continue;
        }

        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("Slave: failed to connect");
            continue;
        }

        break;
    }

    if (p == NULL) {
        throw std::runtime_error("Failed to connect");
    }

    inet_ntop(p->ai_family, Utils::get_in_addr((struct sockaddr *)p->ai_addr),
            s, sizeof s);
    printf("Slave: connecting to %s\n", s);

    freeaddrinfo(servinfo); // all done with this structure

    // Sending msg to initiate dialog
    if (send(sockfd, CONNECTION_MSG, strlen(CONNECTION_MSG), 0) == -1)
        perror("Slave: sending Hello!");
    // Receiving ACK
    if ((numbytes = recv(sockfd, buf, strlen(CONNECTION_MSG), 0)) == -1)
    {
        perror("Slave: failed to recv the connection msg");
        exit(1);
    }
    buf[numbytes] = '\0';
    printf("Slave: received '%s'\n",buf);
    if (std::string(buf) == CONNECTION_MSG)
        printf("Slave: ACK received\n");
    else
        exit(1);

    sockfd_ = sockfd;
}
