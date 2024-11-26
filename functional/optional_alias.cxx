#include <variant>

struct nothing_t {};

template <typename T>
using optional = std::variant<nothing_t, T>;
