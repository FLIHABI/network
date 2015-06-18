#include "service.hh"

using namespace network;

Service::Service(network::NetworkMode mode)
  : mode_(mode)
  , ready_(false)
  , alive_(false)
  , task_id_counter_(0)
{}

void Service::start()
{
  alive_.store(true, std::memory_order_release);
  svc_th_ = std::thread(&Service::run, this);

  while (!ready_.load(std::memory_order_acquire))
    std::this_thread::yield();
}

void Service::stop()
{
  require_stop();

  svc_th_.join();
}

//TODO: take a ref to Ressource Manager ?
unsigned Service::add_task(int16_t fun_id, std::vector<int64_t>& params)
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
task::Task& Service::get_task_result(unsigned id)
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


void Service::run()
{
  ready();
  switch (mode_)
  {
    case SERVER:
      server_thread();
      break;

    case CLIENT:
      client_thread();
      break;
  }
}

void Service::client_thread()
{
  while (alive_.load(std::memory_order_acquire))
  {
    //TODO: client part
  }
}

void Service::server_thread()
{
  while (alive_.load(std::memory_order_acquire))
  {
    //TODO: server part
  }
}

Service::~Service()
{}
