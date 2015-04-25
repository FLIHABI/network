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

/*
 * Listen on a port until packet comes.
 * WARNING: the integet returned is the socketfd used so CLOSE IT AFTER USAGE
 */
int listen(int port);

#include "listener.cc"

#endif   /* ----- #ifndef LISTENER_INC  ----- */
