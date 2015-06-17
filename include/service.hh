#ifndef SERVICE_HH
# define SERVICE_HH

# include <thread>
# include <atomic>
# include <unordered_map>

# include "task.hh"
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
      unsigned task_id_counter_;
      std::unordered_map<unsigned, task::Task> tasks_;

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

      //TODO: take a ref to Ressource Manager ?
      inline unsigned add_task(int16_t fun_id, std::vector<int64_t>& params)
      {
        tasks_.insert(
            std::make_pair( task_id_counter_,
              task::Task(task_id_counter_, fun_id, params)));

        //task::Task& task = tasks_.at(task_id_counter_); //TODO: network
        //TODO: pass these datas to the network thread
        //auto network_datas = serialize_call(fun_id, params);
        //std::cout << "Vector has " << network_datas.size() << " elts" << std::endl;
        //std::string aux((char*)&network_datas[0], network_datas.size() * 8);
        //std::cout << "String has " << aux.size() << " elts" << std::endl;
        //server_->execBytecode(aux);
        return task_id_counter_++;
      }

      //TODO: take a ref to Ressource Manager ?
      inline task::Task& get_task_result(unsigned id)
      {
        auto iter = tasks_.find(id);

        if (iter == tasks_.end())
          throw std::invalid_argument(
              "Unknown task id: " + std::to_string(id));

        while (!iter->second.is_complete)
          std::this_thread::yield();

        return iter->second;

        //FIXME while (!iter->second.is_complete)
        //TODO: move that to server's thread
        //Result* r;
        //while ((r = server_->getResult(id)) == nullptr)
        //  std::this_thread::yield();

        //std::string& res = r->value;
        //std::vector<uint64_t> result(res.size() / 8);
        //std::cout << "[]String has " << res.size() << " elts" << std::endl;
        //std::cout << "[]Vector has " << result.size() << " elts" << std::endl;
        //std::copy((uint64_t*)&res[0], ((uint64_t*)&res[0]) + res.size() / 8, &result[0]);
        //iter->second.return_value = deserialize_return(result);
        //return iter->second;
      }



  };
}

#endif /* end of include guard: SERVICE_HH */
