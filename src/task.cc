#include "task.hh"

task::Task::Task(unsigned task_id, std::vector<uint64_t>& params)
  : id(task_id)
  , is_complete(false)
  , call_send(params)
{}
