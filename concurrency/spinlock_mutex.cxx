#include <atomic> 
#include <chrono>
#include <iostream>
#include <thread>

class spinlock_mutex 
{
 private:
  std::atomic_flag flag_;
 
 public:
  spinlock_mutex() :
    flag_{ATOMIC_FLAG_INIT}
  {}

  void lock()
  {
    while (flag_.test_and_set(std::memory_order_acquire));
  }

  void unlock()
  {
    flag_.clear(std::memory_order_release);
  }
};

spinlock_mutex lock;

void critical_section(int thread_id) {
    lock.lock(); // get mutex

    std::cout << "thread " << thread_id << " get mutex" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "thread " << thread_id << " free mutex" << std::endl;
    lock.unlock();
}

int main() {
    std::thread t1(critical_section, 1); 
    std::thread t2(critical_section, 2); 

    t1.join(); 
    t2.join(); 

    return 0;
}
