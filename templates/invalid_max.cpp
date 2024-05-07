#include <iostream>
#include <string>
#include <type_traits>
#include <typeinfo>

template< typename T1, typename T2 >
auto max( T1& a, T2& b ) -> decltype(true ? a : b) {
    return (a > b ? a : b);
}

int main()
{   
    int x = 5;
    int y = 1;
    int& ref_x = x;
    int& max_val = max(ref_x, y);
    max_val++;
    std::cout << "reference to x: " << max_val << ' ' << "x: " << x << '\n';
    x++;
    std::cout << "reference to x: " << max_val << ' ' << "x: " << x;
}

