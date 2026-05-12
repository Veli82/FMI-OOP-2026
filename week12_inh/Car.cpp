#include "Car.hpp"
#include <stdexcept>
#include <iostream>

Car::Car(const Car& other) :
Vehicle(other.brand, other.year, other.maxSpeed), hp(other.hp)
{
    setModel(other.model);
}

Car::Car(const char* brand, unsigned year, unsigned maxSpeed, const char* model, unsigned hp) :
Vehicle(brand, year, maxSpeed),  hp(hp)
{
    setModel(model);
}

Car::~Car() { clear(); }

Car& Car::operator=(const Car& other)
{
    if (this == &other) return *this;

    Car temp(other);

    std::swap(model,temp.model);
    std::swap(hp,temp.hp);
    swapData(temp);

    return *this;
}

bool Car::canGoOnTheHighway() const
{
    return maxSpeed >= 50 ? "Yes" : "No";
}

void Car::setModel(const char* model)
{
    if (!model) throw std::invalid_argument("nullptr");
    unsigned len = strlen(model);
    char* temp = new char[len + 1];
    strcpy(temp,model);

    clear();

    this->model = temp;
}

void Car::clear()
{
    delete[] model;
    model = nullptr;
}
