/*
 * ============================================================================
 *       Filename:  slave_main.cc
 *    Description:  Main for testing the slave interaction
 *        Version:  1.0
 *        Created:  04/22/2015 02:17:50 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  Rafael Gozlan, rafael.gozlan@epita.fr
 *   Organization:  Flihabi
 * ============================================================================
 */
#include <stdlib.h>

#include "listener.cc"

int main()
{
    listen(4545);
}
