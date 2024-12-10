#include <list>

template <typename T>
  using MyAllocList = std::list<T, MyAlloc<T>>;

// pre C++11 alias implementation
template <typename T>
struct MyAllocList {
  typedef std::list<T, MyAlloc<T>> type;  
};
// call syntax: MyAllocList<T>::type
