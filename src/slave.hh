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
         * Return: the bytecode string.
         */
        std::string getBytecode();
        /*
         * Send the bytecode result to the server.
         */
        void send_bytecode(std::string);

    private: // Private methods
        std::string getServerAddress();
        void connetToServer();

    private: // Private attributes
        int sockfd_;

}; /* -----  end of class Slave  ----- */

#include "slave.hxx"

#endif   /* ----- #ifndef SLAVE_INC  ----- */
