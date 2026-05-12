#include "Vehicle.hpp"
#include <iostream>
#include <stdexcept>

Vehicle:: ~Vehicle() { clear(); }

Vehicle::Vehicle(const Vehicle& other) :  year(other.year), maxSpeed(other.maxSpeed)
{
    setBrand(other.brand);
}

Vehicle& Vehicle::operator=(const Vehicle& other)
{
    if (this == &other) return *this;

    swapData(other);

    return *this;
}

void Vehicle::setBrand(const char* b)
{
    if (!b)
        throw std::invalid_argument("nullptr");
    unsigned len = strlen(b);

    char* temp = new char[len + 1];
    strcpy(temp, b);

    clear();
    brand = temp;
}

void Vehicle::setYear(unsigned y) { year = y; }

void Vehicle::setMaxSpeed(unsigned speed) { maxSpeed = speed; }

void Vehicle::clear()
{
    delete[] brand;
    brand = nullptr;
}

void Vehicle::swapData(const Vehicle& other)
{
    Vehicle temp(other);

    std::swap(brand, temp.brand);
    std::swap(year,temp.year);
    std::swap(maxSpeed,temp.maxSpeed);
}
