#include <iostream>

class X {
 public:
  X() {
    std::puts("default constructor\n");
  }
  X(const X& other) {
    std::cout << "copy constructor\n";
  }
  X(X&& other) {
    std::cout << "move constructor\n";
  }
};

X foo() {
  X x;
  return x;

  /*
    anti-pattern: NRVO is disabled
    return std::move(x);
  */
}

int main() {
  std::cout << "Hello World\n";
  auto x = foo();
}
