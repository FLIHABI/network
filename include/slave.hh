/*
 * ============================================================================
 *       Filename:  slave.hh
 *    Description:  Slave class declaration
 *        Version:  1.0
 *        Created:  04/26/2015 02:39:58 AM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  Rafael Gozlan, rafael.gozlan@epita.fr
 *   Organization:  Flihabi
 * ============================================================================
 */

#ifndef  SLAVE_INC
#define  SLAVE_INC

#include <string>

/*
 * ============================================================================
 *        Class:  Slave
 *  Description:  Slave class asking for bytecode to the server and returning
 *  the result.
 * ============================================================================
 */
class Slave
{
    public:
        /* ====================  LIFECYCLE  ================================ */
        /*
         * Description: CTor for the slave.
         * Initialize the communication with the server
         */
        Slave ();
        /* ====================  OPERATORS  ================================ */
        /*
         * Wait for the bytecode to be sent by the server.
         * Return: the bytecode string or NULL if failed.
         */
        std::string getBytecode();
        /*
         * Send the bytecode result to the server.
         * Return: 0 for success, -1 for failure
         */
        int send_bytecode(std::string);

    private: // Private methods
        ssize_t sendBytecode(int socket, std::string buffer, size_t len);
        std::string getServerAddress();
        void connectToServer(std::string ip, int port);

    private: // Private attributes
        int sockfd_;

}; /* -----  end of class Slave  ----- */

#endif   /* ----- #ifndef SLAVE_INC  ----- */
