#ifndef TS_QUEUE_HXX
# define TS_QUEUE_HXX

# include <queue>
# include <mutex>
# include <condition_variable>

namespace utils
{
  template<typename T>
  class TSQueue
  {
    public:
      void enqueue(T e)
      {
        std::unique_lock<std::mutex> l(mut_);

        queue_.push(e);

        cond_var_.notify_one();
      }

      T dequeue()
      {
        std::unique_lock<std::mutex> l(mut_);

        cond_var_.wait(l, [&]() {return !queue_.empty();});

        T e = queue_.front();
        queue_.pop();

        return e;
      }

    private:
      std::queue<T> queue_;
      std::mutex mut_;
      std::condition_variable cond_var_;
  };
}

#endif /* end of include guard: TS_QUEUE_HXX */
