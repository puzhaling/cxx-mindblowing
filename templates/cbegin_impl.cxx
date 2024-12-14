
template <typename C> // for C++11
auto cbegin(const C& container) -> decltype(std::begin(container))
{
  return std::begin(container);
}
