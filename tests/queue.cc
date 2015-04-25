/*
 * ============================================================================
 *       Filename:  queue.cc
 *    Description:  Tests for blocking queue
 *        Version:  1.0
 *        Created:  04/24/2015 05:16:23 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  Rafael Gozlan, rafael.gozlan@epita.fr
 *   Organization:  Flihabi
 * ============================================================================
 */
#include <iostream>
#include <queue>

#include "blocking_queue.hh"

int main ()
{
    std::queue<int> q;
    BlockingQueue<int> bq;
    for (int i = 0; i < 42; ++i) {
        bq.push(i);
        q.push(i);
    }
    for (int i = 0; i < 42; ++i) {
        int a = bq.pop();
        int b = q.front();
        q.pop();
        if (a != b) {
            std::cout << "Pop test: failed" << std::endl;
            std::exit(1);
        }
    }
    std::cout << "Pop test: success" << std::endl;
    if (bq.pop() == NULL)
        std::cout << "Empty test: success" << std::endl;
    else
        std::cout << "Empty test: failed" << std::endl;
    return EXIT_SUCCESS;
}        /* ----------  end of function main  ---------- */
