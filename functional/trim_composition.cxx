#include <string>
#include <algorithm>

struct is_not_space {
  inline bool operator()(char ch) {
    return ch == ' ';
  }
};

std::string trim_left(std::string s)
{
  s.erase(s.begin(),
          std::find_if(s.begin(), s.end(), is_not_space));
  return s;
}

std::string trim_right(std::string s)
{
  s.erase(std::find_if(s.rbegin(), s.rend(), is_not_space).base(),
          s.end());
  return s;
}

std::string trim(std::string s)
{
  return trim_left(trim_right(std::move(s));
}
