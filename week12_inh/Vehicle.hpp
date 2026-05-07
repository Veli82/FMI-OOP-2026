#pragma once

class Vehicle {
public:
    //big 4
    Vehicle() = delete;
    virtual ~Vehicle();
    Vehicle(const Vehicle& other);
    Vehicle& operator=(const Vehicle& other);
    Vehicle(const char* brand, unsigned year, unsigned maxSpeed) :
    brand(setBrand(brand)), year(year), maxSpeed(maxSpeed) {}

    //setters
    char* setBrand(const char* b);
    void setYear(unsigned y);
    void setMaxSpeed(unsigned speed);

    //getters
    char* getBrand() const {return brand;}
    unsigned getYear() const {return year;}
    unsigned getMaxSpeed() const {return maxSpeed;}
private:
    void clear();
protected:
    char* brand = nullptr;
    unsigned year;
    unsigned maxSpeed;
};



