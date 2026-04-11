#include <iostream>
#include "../lib/ezlib.h"

class Product{
    public:
        Product() : mName(nullptr), mDescription(nullptr), mPrice(0.0f), mIsAvailable(false) {
            setName("Big black horse c");
            setDescription("o ck"); 
            setPrice(6.7);
            setIsAvailable(true);
        }
        Product(
            const char *name,
            const char *description,
            float price,
            bool isAvailable
        ) : mName(nullptr), mDescription(nullptr), mPrice(0.0f), mIsAvailable(false) {
            setName(name);
            setDescription(description); 
            setPrice(price);
            setIsAvailable(isAvailable);
        }

        Product(const Product& other) : mName(nullptr), mDescription(nullptr), mPrice(0.0f), mIsAvailable(false) {
            setName(other.mName);
            setDescription(other.mDescription);
            setPrice(other.mPrice);
            setIsAvailable(other.mIsAvailable);
        }

        Product& operator=(const Product& other){
            if(this == &other) return *this;

            setName(other.mName);
            setDescription(other.mDescription);
            setPrice(other.mPrice);
            setIsAvailable(other.mIsAvailable);

            return *this;
        }

        bool canBuy(float availableMoney){return mIsAvailable && availableMoney >= mPrice;}

        void printProduct(){
            std::cout << "-- Product --";
            std::cout << "name : " << mName; 
            std::cout << "description : " << mDescription; 
            std::cout << "price : " << mPrice; 
            std::cout << "isAvailable : " << mIsAvailable; 
        }
     
        void setName(const char *name){
            if(!name) throw std::invalid_argument("Name can't be null");

            char* newName = allocCopy(name);
            delete[] mName;
            mName = newName;
        }
        void setDescription(const char *description){
            if(!description) throw std::invalid_argument("Description can't be null");

            char* newDescription = allocCopy(description);
            delete[] mDescription;
            mDescription = newDescription;
        }
        void setPrice(float price) {
            if(price < 0) throw std::invalid_argument("Price should be >= 0");
            mPrice = price;
        }
        void setIsAvailable(bool isAvailable) {mIsAvailable = isAvailable;}
 
        const char *getName() const {return mName;}
        const char *getDescription() const {return mDescription;}
        float getPrice() const {return mPrice;}
        bool getIsAvailable() const {return mIsAvailable;}
        ~Product(){clear();}
    private:
        char* allocCopy(const char* source){
            const size_t len = strlen_t(source);
            char* data = new (std::nothrow) char[len + 1];
            if(!data) throw std::bad_alloc();

            strcpy_t(data, source);
            return data;
        }

        void clear(){
            delete[] mName;
            delete[] mDescription;
            mName = nullptr;
            mDescription = nullptr;
            mPrice = 0.0;
            mIsAvailable = false;
        }

        char *mName;
        char *mDescription;
        float mPrice;
        bool mIsAvailable;
};
 
int main(void){
    
    return 0;
}