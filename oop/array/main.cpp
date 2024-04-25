#include <iostream>
#include <array>

#include "transport.hpp"
#include "array.hpp"

// транспортный пропускной пункт
// если транспорт экологически чистый 
// - пропуск разрешен

//int main() {
    // array<Transport*, 10> transports{};  

    // transports[0] = new ElectricCar{};
    // transports[1] = new Bicycle{};
    // transports[2] = new GasolineCar{};
    // transports[3] = new Bicycle{};
    // transports[4] = new ElectricCar{};
    // transports[5] = new GasolineCar{}; 
    // transports[6] = new Bicycle{}; 
    // transports[7] = new ElectricCar{}; 
    // transports[8] = new GasolineCar{}; 
    // transports[9] = new GasolineCar{}; 
    
    // for (std::size_t i{}; i < 10; ++i)
    // {
    //     std::cout << transports[i];
    //     std::cout << '\n' << '\n';
    // }
//} 

// driver function
int main() 
{
    array<int, 5> ints{};
    ints[0] = 1;
    ints[1] = 2;
    ints[2] = 3;
    ints[3] = 4;
    ints[4] = 5;
    std::cout << "ints size: " << ints.size() << '\n';

    auto it{ ints.begin() };
    auto it1{ ints.begin() + 3 };
    std::cout << (it1 != it1);


    std::cout << "\n\n\n\n";
    for (std::size_t i{}; i < 5; ++i)
        std::cout << ints[i] << '\n';

    std::cout << "[]: " << ints[3] << '\n';

    std::array<int, 1>arr1{ 1 };
    std::array<int, 1>arr2{ 2 };
    swap(arr1, arr2);
    
    std::cout << arr1[0] << '\n';
    std::cout << arr2[0] << '\n';

    std::cout << "\nend - begin: " << ints.end() - ints.begin() << '\n';
    std::cout << "\nbegin - end: " << ints.begin() - ints.end() << '\n';
    array<int, 10> test1{1,2,3,4,5};
    array<int, 21> test2{1,2,3,4,5};
    std::cout << "\nequality test: ";
    std::cout << (test1 == test2) << '\n';
}