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

#define NB_TESTS 10

int main()
{
    Server *s = new Server();
    int ids[NB_TESTS];
    for (int i = 0; i < NB_TESTS; ++i)
        ids[i] = s->execBytecode("This is some bytecode");
    Result *r;
    for (int i = 0; i < NB_TESTS; ++i)
    {
        while ((r = s->getResult(ids[i])) == NULL)
        {
            std::cout << "Server: Waiting for result";
            sleep(1);
        }
        std::cout << "Server received: " << r->value << std::endl;
    }
}
