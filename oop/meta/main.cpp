#include <iostream>
#include <type_traits>

template <long long N>
struct absolute {
    static constexpr long long value = N < 0 ? -N : N;
};

template<long long N>
struct digitsum {
    static constexpr long long value = (N < 0) ? digitsum<absolute<N>::value>::value : N % 10 + digitsum<N / 10>::value;
};

template<>
struct digitsum<0> {
    static constexpr long long value = 0;
};

int main() {
    std::cout << digitsum<123>::value << std::endl; // For positive numbers
    std::cout << digitsum<-123>::value << std::endl; // For negative numbers
    return 0;
}
