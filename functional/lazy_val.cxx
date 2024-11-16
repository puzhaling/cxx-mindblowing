#include <functional>
#include <memory>
#include <mutex>

// delegete type inference to compiler
// and win in perfomance because of no using
// of universal type for functional (callable) objects
// like std::function
template <typename F>
class lazy_val {
public:
  lazy_val(F computation)
    : m_computation(computation)
    , m_cache_initialized(false)
  {
  }

  operator const decltype(m_computation())& () const 
  {
    std::call_once(m_value_flag, [this] {
      m_cache = m_computation();
    });

    return m_cache;
  }

private:
  F m_computation;
  // must be default constructible
  mutable decltype(m_computation()) m_cache; 
  mutable std::once_flag m_value_flag;
};

// pre C++17 code template
// to have template type deduction for template types
// (works for template functions)
template <typename F>
inline lazy_val<F> make_lazy_val(F&& computation)
{
  return lazy_val<F>(std::forward<F>(computation);
}
