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
    Server *s = new Server();
    int id = s->execBytecode("This is some bytecode");
    Result *r;
    while ((r = s->getResult(id)) == NULL);
    std::cout << "Server received: " << r->value << std::endl;
    sleep(20);
}
