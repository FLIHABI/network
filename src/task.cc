#include "task/task.hh"

task::Task::Task(unsigned task_id, int16_t fun_id, std::vector<int64_t>& params)
  : id(task_id)
  , is_complete(false)
  , fun_id(fun_id)
  , params(params)
{}
