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
#include <iostream>

#include "server.hh"

#define NB_TESTS 10

int main()
{
    Server *s = new Server();
    int ids[NB_TESTS];
    std::string string = "This is some bytecode";
    string += '\0';
    string += "This is something else";
    for (int i = 0; i < NB_TESTS; ++i)
        ids[i] = s->execBytecode(string);
    Result *r;
    for (int i = 0; i < NB_TESTS; ++i)
    {
        while ((r = s->getResult(ids[i])) == NULL)
        {
            std::cout << "Server: Waiting for result nb " << i << "\n";
            sleep(1);
        }
        std::cout << "Server received: " << r->value << std::endl;
    }
}
