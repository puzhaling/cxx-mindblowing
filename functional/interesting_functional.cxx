#include <iostream>
#include <string>
#include <functional>

int main() {
  std::string str{"A small pond"};
  std::function<bool(std::string)> f;

  // std::function allows to encapsulate
  // all types of invokable (not be confused with
  // callable) objects
  f = &std::string::empty;

  std::cout << f(str);
}
