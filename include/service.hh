#ifndef SERVICE_HH
# define SERVICE_HH

# include <thread>
# include <atomic>

# include "network_mode.hh"

namespace network
{
  class Service
  {
    public:
      Service(network::NetworkMode mode);
      ~Service();

      void start();
      void stop();

    private:
      std::thread svc_th_;
      network::NetworkMode mode_;
      std::atomic<bool> ready_;
      std::atomic<bool> alive_;

      void run();
      void client_thread();
      void server_thread();

      inline void require_stop()
      {
        alive_.store(false, std::memory_order_release);
      }

      inline void ready()
      {
        ready_.store(true, std::memory_order_release);
      }
  };
}

#endif /* end of include guard: SERVICE_HH */
