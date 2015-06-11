/*
 * ============================================================================
 *       Filename:  blocking_queue.hh
 *    Description:  Blocking queue implementation for flihabi network
 *        Version:  1.0
 *        Created:  04/23/2015 10:01:39 PM
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  Rafael Gozlan, rafael.gozlan@epita.fr
 *   Organization:  Flihabi
 * ============================================================================
 */


#ifndef  BLOCKING_QUEUE_INC
#define  BLOCKING_QUEUE_INC

#include <queue>
#include <mutex>

/*
 * ============================================================================
 *        Class:  BlockingQueue
 *  Description:  Basic blocking queue for network usage
 * ============================================================================
 */
template <class T>
class BlockingQueue
{
    public:
        /* ====================  LIFECYCLE  ================================ */
        BlockingQueue();                             /* constructor */

        /* ====================  ACCESSORS  ================================ */
        T pop();

        /* ====================  MUTATORS   ================================ */
        void push(T e);

    private:
        /* ====================  DATA MEMBERS  ============================= */
        std::queue<T> q_;
        std::mutex q_lock_;

}; /* ----------  end of template class BlockingQueue  ---------- */

#include "blocking_queue.hxx"

#endif   /* ----- #ifndef BLOCKING_QUEUE_INC  ----- */
