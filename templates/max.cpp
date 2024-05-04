#include <iostream>
#include <type_traits>

template< typename T1, 
    typename RT = std::decay_t<decltype(T1())> >
RT max( T1 const& a, T1 const& b ) {
    return (a > b) ? a : b;
} 
template< typename T1, typename T2,
    typename RT = std::common_type_t<T1, T2> >
RT max( T1 const& a, T2 const& b ) {
    return (a > b) ? a : b; 
}

int main() {
    std::cout << max(1, 2) << '\n';
    std::cout << max(2.5, 1);
    return 0;
}
