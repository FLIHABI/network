/*
 * ============================================================================
 *       Filename:  listener.hh
 *    Description:  Listener header
 *        Version:  1.0
 *        Created:  04/25/2015 06:57:31 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  Rafael Gozlan, rafael.gozlan@epita.fr
 *   Organization:  Flihabi
 * ============================================================================
 */


#ifndef  LISTENER_INC
#define  LISTENER_INC

#include <string>

struct Socket
{
    int sockfd;
    std::string msg;
    std::string ip;
};

/*
 * Listen on a port until packet comes.
 * WARNING: the integer returned is the socketfd used so CLOSE IT AFTER USAGE
 */
Socket *listen(int port);

#endif   /* ----- #ifndef LISTENER_INC  ----- */
