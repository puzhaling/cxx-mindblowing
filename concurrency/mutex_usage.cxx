#include <vector>
#include <mutex>
#include <algorithm>

std::vector<int> vec;
std::mutex some_mutex;

void add_to_list(int new_value)
{
  // RAII wrapper for any mutex
  std::lock_guard<std::mutex> guard(some_mutex);
  vec.push_back(new_value);
}

bool vec_contains(int value_to_find)
{
  // if some_mutex is blocked in add_to_list, execution stops here
  std::lock_guard<std::mutex> guard(some_mutex);
  return std::find(vec.begin(), vec.end(), value_to_find)
      != vec.end();
}
