#include <iostream>
#include <string>

template < typename T >
T max( T a, T b ) {
  return b < a ? a : b;
}

void greet_by_name( std::string const & name ) {
  std::cout << "Hello, " << name << '\n';
}

int main() {
  greet_by_name("Hermann");
  std::cout << ::max(2,5);
  return 0;
}
