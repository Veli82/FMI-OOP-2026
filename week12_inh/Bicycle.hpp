#pragma once

#include "Vehicle.hpp"

class Bicycle : public Vehicle {
public:
    //constructor
    Bicycle(const char* brand, unsigned year, unsigned maxSpeed, unsigned gears, bool hasBell);

    //functionality
    bool isNew() const;

    //setters
    void setGears(unsigned gears) { this->gears = gears; }
    void setBell(bool bell) { hasBell = bell; }

    //getter
    unsigned getGears() const {return gears;}
    unsigned getHasBell() const {return hasBell;}
public:
    unsigned gears;
    bool hasBell;
};
