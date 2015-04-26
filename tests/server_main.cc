/*
 * ============================================================================
 *       Filename:  server_main.cc
 *    Description:  Server main for testing
 *        Version:  1.0
 *        Created:  04/25/2015 06:37:53 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  Rafael Gozlan, rafael.gozlan@epita.fr
 *   Organization:  Flihabi
 * ============================================================================
 */
#include <stdlib.h>
#include <unistd.h>

#include "server.hh"

int main()
{
    Server s(4545);
    sleep(20);
}
