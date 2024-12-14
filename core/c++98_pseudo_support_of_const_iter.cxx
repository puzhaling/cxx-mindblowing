#include <vector>

int main() {
  typedef std::vector<int>::iterator IterT;
  typedef std::vector<int>::const_iterator ConstIterT;

  std::vector<int> values;

  // in c++98 there is no simple way to get const iterator
  // to non-const container;
  ConstIterT ci =
    std::find(static_cast<ConstIterT>(values.begin()),
              static_cast<ConstIterT>(values.end()),
              1983);

  // in c++98 only non const iterators can 
  // point to insert/delete positions
  values.insert(static_cast<IterT>(ci), 1998);

  // another way to get const iterator to non const container
  const std::vector<int>& ref_values = values;
  ci = std::find(values.begin(), values.end(), 1983); 

  // ^^ such a crooked ways, isn't it?


  // c++11 feature to get const iterator to non const
  // container is so simple, watch it:
  auto const_it = values.cbegin(); // .cend()



  // fun fact: due to oversight in process of standartization
  // of c++11, only non member functions begin() and end() were added,
  // but not cbegin(), cend(), rbegin(), rend() and etc. it was
  // corrected in c++14
}
