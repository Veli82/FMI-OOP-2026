#include "Vehicle.hpp"
#include <iostream>
#include <stdexcept>

Vehicle:: ~Vehicle() { clear(); }

Vehicle::Vehicle(const Vehicle& other) : brand(setBrand(other.brand)), year(other.year), maxSpeed(other.maxSpeed) {}

Vehicle& Vehicle::operator=(const Vehicle& other)
{
    if (this == &other) return *this;

    Vehicle temp(other);

    std::swap(brand,temp.brand);
    std::swap(maxSpeed, temp.maxSpeed);
    std::swap(year,temp.year);

    return *this;
}

char* Vehicle::setBrand(const char* b)
{
    if (!b)
        throw std::invalid_argument("nullptr");
    unsigned len = strlen(b);

    char* temp = new char[len + 1];
    strcpy(temp, b);

    return temp;
}

void Vehicle::setYear(unsigned y) { year = y; }

void Vehicle::setMaxSpeed(unsigned speed) { maxSpeed = speed; }

void Vehicle::clear()
{
    delete[] brand;
    brand = nullptr;
}
