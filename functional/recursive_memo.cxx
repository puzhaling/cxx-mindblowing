#include <map>
#include <type_traits>
#include <tuple>
#include <mutex>

namespace detail {
  class null_param {};
}

template <typename Sig, typename F>
class memoize_helper;

template <typename Result, typename... Args, typename F>
class memoize_helper<Result(Args...), F> {
private:
  using function_type = F;
  using args_tuple_type = std::tuple<std::decay_t<Args>...>;
  
  function_type f;
  mutable std::map<args_tuple_type, Result> m_cache;
  mutable std::recursive_mutex m_cache_mutex;

public:
  template <typename Function>
  memoize_helper(Function&& f, null_param) 
    : f(f)
  {
  }

  memoize_helper(const memoize_helper& other) 
    : f(other.f)
  {
  }
  
  template <typename... InnerArgs>
  Result operator()(InnerArgs&&... args) const
  {
    std::unique_lock<std::recursive_mutex>
        lock{m_cache_mutex};

    const auto args_tuple = 
        std::make_tuple(args...);
    const auto cached = m_cache.find(args_tuple);

    if (cached != m_cache.end()) {
      return cached->second;
    } else {
      auto&& result = f(
        *this,
        std::forward<InnerArgs>(args)...);
      m_cache[args_tuple] = result;
      return result;
    }
  }
};

template <typename Sig, typename F>
memoize_helper<Sig, std::decay_t<F>>
make_memoized_r(F&& f)
{
  return {std::forward<F>(f), detail::null_param);
}

template <typename F>
unsigned int fib(F&& fibmemo, unsigned int n) 
{
  return n == 0 ? 0
       : n == 1 ? 1
       : fibmemo(n - 1) + fibmemo(n - 2);
}

int main()
{
  auto fibmemo = make_memoized_r<
            unsigned int(unsigned int)>(
       [](auto& fib, unsigned int n) {
         return n == 0 ? 0
              : n == 1 ? 1
              : fib(n - 1) + fib(n - 2);
       });
}
