#include <iostream>
#include <type_traits>

int main() {
  // common case
  if (std::copy_assignable_v<int>) {
    std::cout << "int is assignable to each other (l-values)\n";
  }
  // need to explicitly choose value category: lvalue, pr-value and etc
  if (!(std::assignable_v<int, int>)) {
    std::cout << "pr-value cannot be assigned to int pr-value\n";
  }
  return 0;
}
