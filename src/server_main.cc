/*
 * ============================================================================
 *       Filename:  server_main.cc
 *    Description:  Main for testing server interaction
 *        Version:  1.0
 *        Created:  04/22/2015 02:22:29 PM
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
    s.launchServer();
    sleep(10);
}
