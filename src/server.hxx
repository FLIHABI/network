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

Server::Server(int port)
{
    port_ = port;
    // Launch the server broadcaster and connection handler
    std::thread broadcaster(broadcastLoop);
    std::thread handler(Server::handler);
}


/* Getter for slaves result (Thread-safe access) */

Result Server::getResult(int i)
{
    slave_result_mutex.lock();
    std::string r = slaves_results_[i];
    if (r.size() != 0)
       slaves_results_[i] = "";
    slave_result_mutex.unlock();
    return r;
}

void Server::setResult(int i, std::string s)
{
    slave_result_mutex.lock();
    slaves_results_[i] = s;
    slave_result_mutex.unlock();
}

void Server::addSlave(int s)
{
    slave_mutex.lock();
    slaves_.push_back(s);
    busy_.push_back(false);
    slave_mutex.unlock();
}

void Server::removeSlave(int s)
{
    slave_mutex.lock();
    for (size_t i = 0; i < slaves_.size(); ++i)
    {
        int socket = slaves_[i];
        if (socket == s)
        {
            slaves_.erase(slaves_.begin()+i);
            busy_.erase(busy_.begin()+i);
        }
    }
    slave_mutex.unlock();
}


/* Server slaves handling */
void Server::slaveHandler()
{
}
