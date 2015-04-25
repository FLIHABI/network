/*
 * ============================================================================
 *       Filename:  blocking_queue.hxx
 *    Description:  Blocking queue method definition
 *        Version:  1.0
 *        Created:  04/24/2015 04:04:37 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  Rafael Gozlan, rafael.gozlan@epita.fr
 *   Organization:  Flihabi
 * ============================================================================
 */

#include "blocking_queue.hh"

template <class T>
BlockingQueue<T>::BlockingQueue() : q_()
{}

template <class T>
void BlockingQueue<T>::push(T e)
{
    q_lock_.lock();
    q_.push(e);
    q_lock_.unlock();
}

template <class T>
T BlockingQueue<T>::pop()
{
    T e;
    q_lock_.lock();
    if (q_.empty())
        e = NULL;
    else
    {
        e = q_.front();
        q_.pop();
    }
    q_lock_.unlock();
    return e;
}
