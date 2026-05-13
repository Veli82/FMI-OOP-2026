#include "Bicycle.hpp"

Bicycle::Bicycle(const char* brand, unsigned year, unsigned maxSpeed, unsigned gears, bool hasBell) :
Vehicle(brand, year, maxSpeed), gears(gears), hasBell(hasBell) {}

bool Bicycle::isNew() const { return year > 2016; }