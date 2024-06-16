#include <vector>
#include <iostream>

template<typename T>         // cast to prevent size effects
auto len(T const& t) -> decltype((void)(t.size()), typename T::size_type()) {
  return t.size();
}

int main() {
  std::vector<int> a = {1,2,3,4,5};
  return len(a);
}
