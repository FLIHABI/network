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

unsigned Service::submit_task(std::string bytecode)
{
  return srv_->execBytecode(bytecode);
}

std::string Service::get_task()
{
  return bytecodes_.dequeue();
}

std::string Service::get_task_result(unsigned id)
{
  Result* r;

  while (!(r = srv_->getResult(id)))
    std::this_thread::yield();

  return r->value;
}

void Service::submit_task_result(std::string result)
{
  results_.enqueue(result);
}

void Service::run()
{
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
  slv_.reset();
  slv_ = std::make_unique<Slave>();

  ready();

  while (alive_.load(std::memory_order_acquire))
  {
    std::string bytecode = slv_->getBytecode();

    bytecodes_.enqueue(bytecode);
    slv_->send_bytecode(results_.dequeue());
  }
}

void Service::server_thread()
{
  srv_.reset();
  srv_ = std::make_unique<Server>();

  ready();

  while (alive_.load(std::memory_order_acquire))
    std::this_thread::yield();
}

Service::~Service()
{}
