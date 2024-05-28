#include <iostream>
void foo() {
    int* x;
    int z;
    int y;
    if (x == nullptr) {
        std::cout << "yes";
    }
    std::cout << x << ' ' << y << ' ' << ' ' << z;
    if (y == 0) {
        std::cout << "yes";
    }

    
}

int main()
{
    foo();
}
