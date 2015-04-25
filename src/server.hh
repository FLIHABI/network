/*
 * ============================================================================
 *       Filename:  server.hh
 *    Description:  server class declaration
 *        Version:  1.0
 *        Created:  04/20/2015 05:48:55 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  Rafael Gozlan
 *   Organization:  Flihabi
 * ============================================================================
 */

#ifndef  SERVER_INC
#define  SERVER_INC

#include <vector>
#include <string>
#include <thread>
#include <mutex>

#include "blocking_queue.hh"

struct Result
{
    std::string value;
};

/*
 * ============================================================================
 *        Class:  Server
 *  Description:  Server laucher
 * ============================================================================
 */
class Server
{
    public:
        Server(int port);
        int execBytecode(std::string bytecode);
        static void handler();


        /* Getter for slaves result */
        Result getResult(int i);

        std::vector<std::string> slaves_results_; /* Slaves results */


    private:
        std::vector<bool> busy_;    /* Slaves busyness */
        BlockingQueue<int> result_; /* Slaves results */
        int port_;

}; /* -----  end of class Server  ----- */

# include "server.hxx"

#endif   /* ----- #ifndef SERVER_INC  ----- */

