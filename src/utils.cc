/*
 * ============================================================================
 *       Filename:  utils.cc
 *    Description:  Tools for networking
 *        Version:  1.0
 *        Created:  06/10/2015 08:24:00 PM
 *       Revision:  none
 *         Author:  Rafael Gozlan
 *   Organization:  Flihabi
 * ============================================================================
 */

#include "utils.hh"

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}
