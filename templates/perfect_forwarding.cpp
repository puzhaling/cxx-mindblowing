#include <utility>
#include <iostream>

class X {

};

void g(X&) {
    std::cout << "g() for variable";
}

void g(X const&) {
    std::cout << "g() for constant";
}

void g(X&&) {
    std::cout << "g() for movable object";
}

template<typename T>
void f(T&& val) { // <= universal reference
    g(std::forward<T>(val));
}

int main() {
    return 0;
}
