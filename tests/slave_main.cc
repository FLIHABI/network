/*
 * ============================================================================
 *       Filename:  slave_main.cc
 *    Description:  Slave main for testing
 *        Version:  1.0
 *        Created:  04/25/2015 06:33:58 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  Rafael Gozlan, rafael.gozlan@epita.fr
 *   Organization:  Flihabi
 * ============================================================================
 */
#include <unistd.h>
#include <string>
#include <iostream>

#include "listener.hh"
#include "slave.hh"

int main()
{
    Slave *s = new Slave();
    while (true)
    {
        std::string b = s->getBytecode();
        sleep(3);
        std::cout << "Sending result"  << std::endl;
        s->send_bytecode("This is some result");
    }
}
