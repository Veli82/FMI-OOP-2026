#include <iostream>
#include "../lib/ezlib.h"

class Beverage{
    public:
        Beverage() : mIsAlcoholic(false), mPrice(0.0f), mName(nullptr) {
            setName("Water");
            setIsAlcoholic(false);
            setPrice(1.5f);
        }
        Beverage(const char* name, bool isAlcoholic, float Price) : mIsAlcoholic(false), mPrice(0.0f), mName(nullptr) {
            setName(name);
            setIsAlcoholic(isAlcoholic);
            setPrice(Price);
        }
        Beverage (const Beverage& other) : mIsAlcoholic(false), mPrice(0.0f), mName(nullptr) {
            setName(other.mName);
            setIsAlcoholic(other.mIsAlcoholic);
            setPrice(other.mPrice);
        }
        Beverage& operator=(const Beverage& other){
            if(this == &other) return *this;
            
            setName(other.mName);
            mIsAlcoholic = other.mIsAlcoholic;
            mPrice = other.mPrice;

            return *this;
        }
        ~Beverage(){delete [] mName;}

        void printBeverage(){
            std::cout << "-- Beverage -- " << std::endl;
            std::cout << "Name: " << mName << std::endl;
            std::cout << "Birth IsAlcoholic: " << mIsAlcoholic << std::endl;
            std::cout << "Price: " << mPrice << std::endl;
        }
        void setName(const char *name) {
            if(!name) throw std::invalid_argument("Name can't be empty");
            const size_t len = strlen_t(name);

            char* newName = new (std::nothrow) char[len + 1];
            if(!newName) throw std::bad_alloc();

            strcpy_t(newName, name);

            delete [] mName;
            mName = newName;
        }
        void setIsAlcoholic(bool isAlcoholic) {mIsAlcoholic = isAlcoholic;} 
        void setPrice(float Price) {
            if(Price < 0.0f)
                throw std::invalid_argument("Price should be >= 0");
            mPrice = Price;
        }
        const char* getName() const {return mName;}
        bool getIsAlcoholic() const {return mIsAlcoholic;} 
        float getPrice() const {return mPrice;}
    private:
        bool mIsAlcoholic;
        float mPrice;
        char *mName;
};

int main(void){
    
    return 0;
}