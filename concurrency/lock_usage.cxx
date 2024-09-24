class some_big_object;

void swap(some_big_object& lhs, some_big_object& rhs);

class X
{
 private:
  some_big_object some_detail;
  std::mutex m;
 
 public:
  X(some_big_object const& sd) : some_detail(sd) {}
  friend void swap(X& lhs, X& rhs)
  {
    // not only swap on the same objects is useless
    // as locking a locked mutex leads to UB
    if (&lhs == &rhs)
      return;
    
    std::lock(lhs.m, rhs.m);
    // last param says not to lock mutex in constructor
    // lock_guards now only take over an exisiting mutex lock
    std::lock_guard<std::mutex> lock_a(lhs.m, std::adopt_lock); 
    std::lock_guard<std::mutex> lock_b(rhs.m, std::adopt_lock); 
    swap(lhs.some_detail, rhs.some_detail);
  }

/*
  friend void swap(X& lhs, X& rhs)
  {
    if (&lhs == &rhs)
      return;
    
    std::scoped_lock guard(lhs.m, rhs.m);
    swap(lhs.some_detail, rhs.some_detail);
  }
*/
}
