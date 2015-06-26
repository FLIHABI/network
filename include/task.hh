#ifndef TASK_HH
# define TASK_HH

# include <cstdint>
# include <vector>

namespace task
{
  struct Task
  {
    Task(unsigned task_id, std::vector<uint64_t>& params);

    unsigned id;
    bool is_complete;
    std::vector<uint64_t> call_send;
    std::vector<uint64_t> call_recv;
  };
}

#endif /* end of include guard: TASK_HH */
