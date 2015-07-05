/*
 * ============================================================================
 *       Filename:  utils.cc
 *    Description:  Tools for networking
 *        Version:  1.0
 *        Created:  06/10/2015 08:24:00 PM
 *       Revision:  none
 *         Author:  Rafael Gozlan
 *   Organization:  Flihabi
 * ============================================================================
 */

#include "utils.hh"
#include <iostream>

// get sockaddr, IPv4 or IPv6:
void* Utils::get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

// Network protocoled functions

unsigned int Utils::recvBytecodeLen(int socket)
{
    int nbytes = -1;
    char clen[sizeof(unsigned int)];
    if ((nbytes = recv(socket, clen, sizeof(unsigned int), 0)) == -1)
    {
        perror("Server recv: failed receiving bytecode");
        return -1;
    }
    unsigned int len;
    memcpy(&len, &clen[0], sizeof(unsigned int));
    return len;
}

ssize_t Utils::sendBytecode(int socket, std::string& buffer, unsigned int len)
{
    std::cout << "Send: ";
    for (unsigned i = 0; i < len; i++)
    {
        if (buffer[i] <= '~' && buffer[i] >= ' ')
            printf("%c", buffer[i]);
        else
            printf("\\%02X", buffer[i]);
    }
    std::cout << "\n==\n";
    char clen[sizeof(unsigned int)];
    ssize_t size = 0;
    memcpy(&clen[0], &len, sizeof(unsigned int));
    if (send(socket, clen, sizeof(clen), 0) == -1)
    {
        perror("Send: failed sending bytecode length!");
        return -1;
    }
    if ((size = send(socket, buffer.c_str(), len, 0)) == -1)
        perror("Send: failed sending bytecode!");
    return size;
}
