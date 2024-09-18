#include <iostream>
#include <thread>

// each thread must have original function
void hello() {
  std::cout << "Hello Concurrent World\n";
}

int main() {
  std::thread t(hello);
  t.join();
}
