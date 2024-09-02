#include <functional>

int main() 
{
  using namespace std::placeholders;

  int value = 5;

  // because std::bind is difficult for code optimizations
  // we can use lambdas
  auto bound_ = std::bind(std::greater<>, _1, value);  
  auto bound__ = [value](int arg) {
      return std::greater<>(arg, value);       
    };
}
