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

#include "../src/listener.cc"

int main()
{
    listen(4545);
}
