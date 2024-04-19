#include <iostream>

#include "transport.hpp"
#include "array.hpp"

// транспортный пропускной пункт
// если транспорт экологически чистый 
// - пропуск разрешен

int main() {
    array<Transport*, 10> transports{};  

    transports[0] = new ElectricCar{};
    transports[1] = new Bicycle{};
    transports[2] = new GasolineCar{};
    transports[3] = new Bicycle{};
    transports[4] = new ElectricCar{};
    transports[5] = new GasolineCar{}; 
    transports[6] = new Bicycle{}; 
    transports[7] = new ElectricCar{}; 
    transports[8] = new GasolineCar{}; 
    transports[9] = new GasolineCar{}; 
    
    for (std::size_t i{}; i < 10; ++i)
    {
        std::cout << transports[i];
        std::cout << '\n' << '\n';
    }
} 
