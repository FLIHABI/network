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

#ifndef  UTILS_HH
# define  UTILS_HH

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string>

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa);

#endif   /* !UTILS_HH */
