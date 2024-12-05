#include <optional>

template <typename T1, typename F>
auto map(const std::optional<T1>& opt, F f)
  -> decltype(std::make_optional(f(opt.value)))
{
  if (opt) {
    return std::make_optional(f(opt.value));
  } else {
    return {};
  }
}
