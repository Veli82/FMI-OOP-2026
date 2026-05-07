#include "Car.hpp"
#include <stdexcept>
#include <iostream>

Car::Car(const Car& other) :
Vehicle(other.brand, other.year, other.maxSpeed),
model(setModel(other.model)), hp(other.hp) {}

Car::Car(const char* brand, unsigned year, unsigned maxSpeed, const char* model, unsigned hp) :
Vehicle(brand, year, maxSpeed), model(setModel(model)), hp(hp) {}

Car::~Car() { clear(); }

Car& Car::operator=(const Car& other)
{
    if (this == &other) return *this;

    Car temp(other);
    clear();

    std::swap(model,temp.model);
    std::swap(hp,temp.hp);
    std::swap(brand,temp.brand);
    std::swap(year,temp.year);
    std::swap(maxSpeed,temp.maxSpeed);

    return *this;
}

bool Car::canGoOnTheHighway() const
{
    return maxSpeed >= 50 ? "Yes" : "No";
}

char* Car::setModel(const char* model)
{
    if (!model) throw std::invalid_argument("nullptr");
    unsigned len = strlen(model);
    char* temp = new char[len + 1];
    strcpy(temp,model);

    return temp;
}

void Car::clear()
{
    delete[] model;
    model = nullptr;
}
