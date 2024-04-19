#ifndef TRANSPOR_HPP
#define TRANSPORT_HPP

#include <concepts>
#include <iostream>
#include <string>

// за итераторы баллы стоят
// внедрить предметную область в самостоятельно реализованный контейнер контейнер

class Transport
{
public:
    virtual void drive() const = 0;

    int cost;
    int weight;
    int height;
};

struct Battery {};
struct GasEngine {}; 
struct CarBody {};
struct Wheel {};

class Car : public Transport
{
public:
    virtual void drive() const = 0;

    Wheel   m_wheels[4];
    CarBody body;
};

class Bicycle : public Transport
{
public:
    void drive() const override 
    {
        std::cout << "Driving the bicycle\n";
    }
    void oilTheChain() const
    {
        std::cout << "Oiling the chain\n";
    } 

    Wheel m_wheels[2];
};

class ElectricCar : public Car
{
public:
    void drive() const override 
    {
        std::cout << "Driving the electric car\n";
    }
    void recharge() const 
    {
        std::cout << "Recharging the electric car\n";
    }
    Battery getBattery() const 
    {
        return m_engine;
    }
private:
    Battery m_engine;
};

class GasolineCar : public Car 
{
public:
    void drive() const override 
    {
        std::cout << "Driving the gasoline car\n";
    }
    void refuel() const
    {
        std::cout << "Refueling the gasoline car\n";
    }

    GasEngine m_engine;
};

std::ostream& operator<<(std::ostream& out, Transport* transport)
{
    out << "car info:\n";
    out << "---------\n";

    if (Bicycle* b = dynamic_cast<Bicycle*>(transport); b != nullptr) 
    {
        out << "wheels count: " << 
            (sizeof(b->m_wheels) / sizeof(decltype(b->m_wheels[0]))) << '\n';
        out << "engine type: no engine\n";
        out << "You are welcome, sir! We've got a cycle lane for you. Just follow the signs.";
    }
    else if (GasolineCar* c = dynamic_cast<GasolineCar*>(transport); c != nullptr)
    {
        out << "wheels count: " << 
            (sizeof(c->m_wheels) / sizeof(c->m_wheels[0])) << '\n';
        out << "engine type: gasoline engine\n";
        out << "Good day! I think you car is fully charged, you got a long way for nearest charging station.\n";
    }
    else if (ElectricCar* c = dynamic_cast<ElectricCar*>(transport); c != nullptr)
    {
        out << "wheels count: " <<
            (sizeof(c->m_wheels) / sizeof(c->m_wheels[0])) << '\n';
        out << "engine type: electric engine\n";
        out << "Oooh, I am sorry, but I can not let you pass. But in a 200 metres you can use a carsharing service.\n";
    }
    else 
    {
        out << "undefined\n";
    }
    return out;
}

template <typename Transport>
concept HumanEnergyFree = (std::derived_from<Transport, Car> == true); 

template <typename Transport>
concept HumanEnergyCost = (std::derived_from<Transport, Car> == false);

template <typename T>
requires HumanEnergyFree<T>
void printHighwayAllowedDrive(T a)
{
    a.drive();
}

template <typename T>
requires HumanEnergyCost<T>
void printEcoDrive(T a)
{
    a.drive();
}

template <typename T>
concept HasBattery = requires(T a)
{
    a.getBattery();
};

template <typename T>
concept HasChain = requires(T a)
{
    a.oilTheChain();
};


template <typename T>
concept Eco = HasBattery<T> || HasChain<T>;


//int main()
//{
//    Bicycle bycicle{};      
//   GasolineCar gasCar{};   
//    ElectricCar electroCar{};
//    
//    printHighwayAllowedDrive(electroCar);
//    printHighwayAllowedDrive(gasCar);
//
//    printEcoDrive(bycicle);
//}

#endif // TRANSPORT_HPP
