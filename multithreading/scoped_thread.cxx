#include <thread>

class scoped_thread
{
  std::thread t;

 public:
  explicit scoped_thread(std::thread t_):
    t(std::move(t_))
  {
    if (!t.joinable())
      throw std::logic_error("no thread");
  }

  ~scoped_thread() {
      t.join();
  }

  scoped_thread(scoped_thread const&) = delete;
  scoped_thread& operator=(scoped_thread const&) = delete;
}

// some Callable object
struct func;

void f()
{
  int some_local_state = 0;
  
  // grants exclusive ownership (move semantics used)
  scoped_thread t{std::thread(func(some_local_state))};
}
