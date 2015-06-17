#include "service.hh"

using namespace network;

Service::Service(network::NetworkMode mode)
  : mode_(mode)
  , ready_(false)
  , alive_(false)
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
