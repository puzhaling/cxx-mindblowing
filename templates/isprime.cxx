#include <iostream>

template<unsigned p, unsigned d>
struct do_is_prime {
  static constexpr bool value = (p % d != 0) &&
                                do_is_prime<p, d - 1>::value;
};

template<unsigned p, unsigned d>
struct do_is_prime<p, 2> {
  static constexpr bool value = (p % 2 != 0);
};

template<unsigned p>
struct is_prime {
  static constexpr bool value = do_is_prime<p, p / 2>::value;
};

template<>
struct is_prime<0> { static constexpr bool value = false; };
template<>
struct is_prime<1> { static constexpr bool value = false; };
template<>
struct is_prime<2> { static constexpr bool value = true; };
template<>
struct is_prime<3> { static constexpr bool value = true; };

int main() {
  std::cout << is_prime<100000123>::value << '\n';
}
