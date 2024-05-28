#include <iostream>
#include <string>
#include <memory>
#include <type_traits>

template< typename T, typename = std::enable_if<(std::is_integral_v<T>)> >
void Foo(T a) {
    
}

void Foo(std::string s) {
    std::cout << s << '\n';
}

int main() {
    Foo(std::string{"temp"});
    return 0;
}
