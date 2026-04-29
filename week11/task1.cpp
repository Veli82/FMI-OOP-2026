#include <iostream>

class Vehicle{
    public:
        Vehicle(){
            // do smth
        }
        Vehicle(const Vehicle& other){
            setColor(other.mcolor);
            setBrand(other.mbrand);
            this->mmanufactureYear = other.getManufactureYear();
            this->mmaxSpeed = other.getMaxSpeed();
        }
        Vehicle& operator=(const Vehicle& other){
            if(this != &other){
                setColor(other.mcolor);
                setBrand(other.mbrand);
                this->mmanufactureYear = other.getManufactureYear();
                this->mmaxSpeed = other.getMaxSpeed();
            }

            return *this;
        }
        ~Vehicle(){
            delete [] mcolor;
            delete [] mbrand;
        }

        bool setColor(const char *color){
            // copy shit
        }
        bool setBrand(const char *brand){
            // copy shit
        }
        void setManufactureYear(size_t manufactureYear){
            this->mmanufactureYear = manufactureYear;
        }
        void setMaxSpeed(size_t maxSpeed){
            this->mmaxSpeed = maxSpeed;
        }

        const char *getColor() const {
            return this->mcolor;
        }
        const char *getBrand() const {
            return this->mbrand;
        }
        size_t getManufactureYear() const {
            return this->mmanufactureYear;
        }
        size_t getMaxSpeed() const {
            return this->mmaxSpeed;
        }
    private:
        char *mcolor = nullptr;
        char *mbrand = nullptr;
        size_t mmanufactureYear = 0;
        size_t mmaxSpeed = 0;
};  

class Bicycle : Vehicle {
    Bicycle(){
        // copy shit
    }

    bool isNew(){
        return this->getManufactureYear() > 2016;
    }


    public:
        size_t mspeeds;
        bool mhasRing;
};

class Car : Vehicle {
    Car(){
        
    }
    ~Car(){
        delete [] mmodel;
    }

    bool canGoOnTheHighway(){
        return this->getMaxSpeed() > 49;
    }

    public:
        char *mmodel;
        size_t mdoorsCount;
        size_t mpower;
};

int main(){
    Vehicle bmw();


    return 0;
}

