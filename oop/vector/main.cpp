#include <iostream>
#include "vector.hpp"

int main() {
    vector<int> v = {1,2,3,4,5,6};
    v.emplace(v.end(), 10);
    //v.push_back(1);
    //v.push_back(2);
    //v[0] = 5;

    //*(v.begin()) = 10; 
    //*(--v.end()) = 99;
    for (auto i : v) 
        std::cout << i << ' ';
    std::cout << '\n';
    return 0;
}
