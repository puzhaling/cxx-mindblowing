#include <functional>

int main() {
  auto predicate = [limit = 42](auto&& object) {
    return std::forward<decltype(object)>(object).age > limit;
  };

  auto eq_two_types_predicate = [limit = 42](auto first, 
        decltype(first) second) {
    ;
  };

  auto  eq_two_types_predicate_ = [] <typename T> (T&& first, 
        T&& second) {
    ;
  };
}
