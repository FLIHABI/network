#ifndef SERVICE_HH
# define SERVICE_HH

# include <thread>
# include <atomic>
# include <mutex>
# include <unordered_map>

# include "task.hh"
# include "slave.hh"
# include "server.hh"
# include "ts_queue.hxx"
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

      unsigned submit_task(std::string bytecode);
      std::string get_task();
      void submit_task_result(std::string result);
      std::string get_task_result(unsigned id);

      inline NetworkMode get_mode()
      {
        return mode_;
      }

    private:
      std::shared_ptr<Server> srv_;
      std::shared_ptr<Slave> slv_;
      std::thread svc_th_;
      network::NetworkMode mode_;
      std::atomic<bool> ready_;
      std::atomic<bool> alive_;
      unsigned task_id_counter_;
      utils::TSQueue<std::string> bytecodes_;
      utils::TSQueue<std::string> results_;

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
