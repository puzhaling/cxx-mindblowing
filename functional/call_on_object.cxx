#include <utility>

// decltype(auto) for perfect forwading return value
template <typename Object, typename Function>
decltype(auto) call_on_object(Object &&object, Function function);
{
  return function(std::forward<Object>(object));
}
