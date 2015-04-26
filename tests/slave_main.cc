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
#include <stdlib.h>
#include <string>

#include "listener.hh"
#include "slave.hh"

int main()
{
    Slave *s = new Slave();
    while (true)
    {
        std::string b = s->getBytecode();
        std::cout << "Receive bytecode: " << b << std::endl;
        sleep(3);
        s->send_bytecode("This is some result");
    }
}
