#include <iostream>
#include <functional>
#include <iomanip>

int main()
{
  // not partial application
  // all arguments are provided
  auto bound =
    std::bind(std::greater<double>(), 6, 42);

  bool is_6_greater_than_42 = bound();

  auto test = 
    std::bind(std::greater<int>(), 5, std::placeholders::_1);

  std::cout << "5 is greater that..hmmm, 4?\n" << std::boolalpha << test(4) << '\n';
  return 0;
}
