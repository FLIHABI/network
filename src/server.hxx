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

#include "server.hh"
#include "broadcaster.hh"


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

}
