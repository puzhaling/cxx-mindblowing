#include <iostream>
#include <map>
#include <tuple>

// works great for non recursive functions
// works as slow as simple recursive function 
// problem: wrapper cannot fully optimize recursive calls
// solution: recursive_memo.cxx
template <typename Result, typename... Args>
auto make_memoized(Result (*f)(Args...)) 
{
  std::map<std::tuple<Args...>, Result> cache;

  return [f, cache](Args... args) mutable -> Result
  {
    const auto args_tuple =
        std::make_tuple(args...);
    const auto cached = cache.find(args_tuple);

    if (cached == cache.end()) {
      auto result = f(args...);
      cache[args_tuple] = result;
      return result;
    } else {
      return cached->second;
    }
  };
}

int fib(int n) {
  if (n == 0 || n == 1) {
    return n;
  }
  auto result = fib(n-1) + fib(n-2);
  return result;
}

int main() {
  auto fibmemo1 = make_memoized(fib);
  std::cout << fibmemo1(50) << std::endl;
}
