/*
 * ============================================================================
 *       Filename:  server.hxx
 *    Description:  Server side implementation for flihabi network
 *        Version:  1.0
 *        Created:  04/20/2015 06:21:00 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  Rafael Gozlan
 *   Organization:  Flihabi
 * ============================================================================
 */

#define _POSIX_SOURCE
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <thread>
#include <iostream>

#include "blocking_queue.hh"
#include "utils.hh"
#include "server.hh"
#include "broadcaster.hh"
#include "listener.hh"
#include "network.hh"

// TODO: More free

// PUBLIC METHODS

Server::Server() : results_(), busy_(), todo_()
{
    // Launch the server broadcaster and connection handler
    std::thread broadcaster(broadcastLoop);
    broadcaster.detach();
    std::thread handle(Server::handler, this);
    handle.detach();
}

Result *Server::getResult(int i)
{
    Result *r = results_[i];
    if (r != NULL)
    {
        results_[i] = NULL;
        busy_[i] = false;   /* set busy to false so the emplacement is free*/
    }
    return r;
}

int Server::execBytecode(std::string bytecode)
{
    int i = getResultEmplacement();
    TodoItem *t = new TodoItem();
    t->id = i;
    t->bytecode = bytecode;
    todo_.push(t);
    return i;
}

// PRIVATE METHODS

void Server::setResult(int i, Result *r)
{
    results_[i] = r;
}

int Server::getResultEmplacement()
{
    for (size_t i = 0; i < busy_.size(); i++)
    {
        if (!busy_[i])
        {
            busy_[i] = true;
            return i;
        }
    }
    /* Add emplacement */
    busy_.push_back(false);
    results_.push_back(NULL);
    return busy_.size() - 1;
}


/* Server slaves handling */
void Server::handler(Server *server)
{
    int sockfd, new_fd;  // listen on sock_fd, new connection on new_fd
    struct addrinfo hints, *servinfo, *p;
    struct sockaddr_storage their_addr; // connector's address information
    socklen_t sin_size;
    int yes=1;
    char s[INET6_ADDRSTRLEN];
    int rv;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

    if ((rv = getaddrinfo(NULL, std::to_string(CONNECTION_PORT).c_str(),
                    &hints, &servinfo)) != 0)
    {
        fprintf(stderr, "Handler: getaddrinfo: %s\n", gai_strerror(rv));
        return;
    }

    // loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                        p->ai_protocol)) == -1) {
            perror("Handler: socket");
            continue;
        }

        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
                    sizeof(int)) == -1) {
            perror("Handler: setsockopt");
            exit(1);
        }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("Handler: bind");
            continue;
        }

        break;
    }

    if (p == NULL)  {
        fprintf(stderr, "Handler: failed to bind\n");
        return;
    }

    freeaddrinfo(servinfo); // all done with this structure

    if (listen(sockfd, 10) == -1)
    {
        perror("listen");
        exit(1);
    }

    printf("Handler: waiting for connections...\n");

    while (true) /* I love stuff like this */
    {
        sin_size = sizeof their_addr;
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd == -1) {
            perror("Handler: accept");
            continue;
        }

        inet_ntop(their_addr.ss_family,
                Utils::get_in_addr((struct sockaddr *)&their_addr),
                s, sizeof s);
        printf("Handler: got connection from %s\n", s);

        int numbytes;
        char buf[100];
        // Receiving connection msg
        if ((numbytes = recv(new_fd, buf, 100-1, 0)) == -1)
        {
            perror("Server: failed to recv the connection msg");
            exit(1);
        }
        buf[numbytes] = '\0';
        printf("Server: received '%s'\n",buf);
        if (std::string(buf) == CONNECTION_MSG)
        {
            std::thread client(Server::clientThread, server, new_fd);
            client.detach();
        }
    }
}

void Server::clientThread(Server *s, int sockfd)
{
    std::cout << "Client thread: sending Hello!" << std::endl;
    // Sending ACK
    if (send(sockfd, CONNECTION_MSG, strlen(CONNECTION_MSG), 0) == -1)
        perror("Client thread: failed sending Hello!");
    while (true) /* client loop */
    {
        TodoItem *t = NULL;
        while ((t = s->todo_.pop()) == NULL); // Try to get bytecode to exec

        std::cout << "Server thread opening task:\n";
            /*
        const char *buffer = t->bytecode.c_str();
        for (unsigned i = 0; i < t->bytecode.size(); i++)
        {
               if (buffer[i] <= '~' && buffer[i] >= ' ')
               printf("%c", buffer[i]);
               else
               printf("\\%02X", buffer[i]);
        }
            */
        std::cout << "\n==\n";
        // Sending Bytecode
        if (Utils::sendBytecode(sockfd, t->bytecode, t->bytecode.size()) == (uint64_t) -1)
        {
            perror("Client thread: failed sending bytecode");
            s->todo_.push(t);
            break;
        }
        ssize_t nbytes;
        uint64_t len;
        if ((len = Utils::recvBytecodeLen(sockfd)) == (uint64_t) -1)
        {
            perror("Client thread: fail to get bytecode len");
            s->todo_.push(t);
            break;
        }
        uint64_t len_aux = len;
        char *buf = (char*) malloc(len);
        char *aux = buf;
        // Receiving connection msg
        while (len > 0)
        {
            if (len < 4096)
                nbytes = recv(sockfd, aux, len, 0);
            else
                nbytes = recv(sockfd, aux, 4096, 0);
            if (nbytes == -1)
            {
                perror("Client thread: failed receiving bytecode");
                s->todo_.push(t);
                break;
            }
            if (nbytes == 0)
            {
                std::cout << "Client thread: Connection seems to be reset."
                    << std::endl;
                s->todo_.push(t);
                close(sockfd);
                break;
            }
            len -= nbytes;
            aux += nbytes;

        }
        if (nbytes == -1)
        {
            return;
        }
        if (nbytes == 0)
        {
            break;
        }
        // Setting result
        /* TODO: Test if r is persistant */
        std::cout << "Server got returned bytecode\n";
        Result *r = new Result();
        r->value = std::string(buf, len_aux);
        s->setResult(t->id, r);
        free(buf);
    }
}
