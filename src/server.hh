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
#include "listener.hh"

struct Result
{
    std::string value;
};

struct TodoItem
{
    int id;
    std::string bytecode;
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
        /*
         * CTor for the server.
         * Launch the broadcaster and the slave handler.
         */
        Server();

        /*
         * Descritption: execBytecode ask the server to execute a bytecode
         * on another machine.
         *
         * Result: the integer returned is the id of the bytecode to be
         * executed.
         */
        int execBytecode(std::string bytecode);

        /*
         * Description: getResult give back the result of a bytecode executed
         * with the id i.
         *
         * Result: the struct returned is NULL if the bytecode computation
         * is not finished of contain a std::string with the result.
         */
        Result *getResult(int i);

    private: /* Private methods */
        static void handler(Server *s);
        void setResult(int i, Result *r);
        int getResultEmplacement();
        static void clientThread(Server *s, int sockfd);

    private: /* Private structs */
        std::vector<Result*> results_;          /* Slaves results */
        std::vector<bool> busy_;                /* Slaves busyness */
        BlockingQueue<TodoItem*> todo_;         /* Slaves todolist */

}; /* -----  end of class Server  ----- */

#endif   /* ----- #ifndef SERVER_INC  ----- */

