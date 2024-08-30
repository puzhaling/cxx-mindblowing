#include <algoritm>

int f(int previous_count, char c)
{
  return (c != '\n') ? previous_count
                     : previous_count + 1;
}

int count_lines(const std::string &s)
{
  return std::accumulate(
             s.cbegin(), s.cend(),
             0,
             f
         );
}
