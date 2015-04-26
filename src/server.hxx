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

#include <thread>
#include <iostream>

#include "server.hh"
#include "broadcaster.hh"
#include "listener.hh"
#include "network.hh"

// PUBLIC METHODS

Server::Server(int port) : results_(), busy_(), todo_()
{
    port_ = port;
    // Launch the server broadcaster and connection handler
    std::thread broadcaster(broadcastLoop);
    broadcaster.detach();
    std::thread handler(Server::handler);
    handler.detach();
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


// PRIVATE METHODS

void Server::setResult(int i, std::string s)
{
    Result *r = new Result();
    /* TODO: Test if s is persistant */
    r->value = s;
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
    return getResultEmplacement(); /* FIXME: not optimal */
}


/* Server slaves handling */
void Server::handler()
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
            get_in_addr((struct sockaddr *)&their_addr),
            s, sizeof s);
        printf("Handler: got connection from %s\n", s);

        std::thread client(clientThread, new_fd);
    }
}

void Server::clientThread(int s)
{
    std::cout << "Client thread: Hello!" << std::endl;
    if (s)
        return;
}
