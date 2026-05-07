#pragma once
#include "Vehicle.hpp"
class Car : public Vehicle
{
public:
    Car() = delete;
    Car(const Car& other);
    Car(const char* brand, unsigned year, unsigned maxSpeed, const char* model, unsigned hp);
    ~Car();
    Car& operator=(const Car& other);

    //setters
    char* setModel(const char* model);
    void setHp(unsigned hp) { this->hp = hp; }

    //getters
    const char* getModel() const { return model; }
    unsigned getHp() const { return hp; }

    //functionality
    bool canGoOnTheHighway() const;

private:
    void clear();

private:
    char* model;
    unsigned hp;
};

