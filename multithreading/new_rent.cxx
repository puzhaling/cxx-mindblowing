#include <memory>
#include <thread>

void foo() {}

int main() {
  std::thread t1{ foo };
  // terminate is called here, because previous
  // thread is not joined or detached
  t1 = std::thread{ foo };
  t1.join();
}
