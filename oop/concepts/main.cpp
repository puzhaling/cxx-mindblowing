#include <concepts>
#include <iostream>

// за итераторы баллы стоят
// внедрить предметную область в самостоятельно реализованный контейнер контейнер

class Transport
{
public:
    virtual void drive() const = 0;

private:
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
private:
    Wheel   wheels[4];
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
private:
    Wheel wheels[2];
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
private:
    GasEngine m_engine;
};

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


int main()
{
    Bicycle bycicle{};      
    GasolineCar gasCar{};   
    ElectricCar electroCar{};
    
    printHighwayAllowedDrive(electroCar);
    printHighwayAllowedDrive(gasCar);

    printEcoDrive(bycicle);
}
