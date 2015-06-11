#ifndef TASK_HH
# define TASK_HH

# include <cstdint>
# include <vector>

namespace task
{
  struct Task
  {
    Task(unsigned task_id, int16_t fun_id, std::vector<int64_t>& params);

    unsigned id;
    bool is_complete;
    int16_t fun_id;
    std::vector<int64_t> params;
    int64_t return_value;
  };
}

#endif /* end of include guard: TASK_HH */
