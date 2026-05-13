#include <iostream>

class Device {
public:
    Device(const char *manufacturer){
        setManufacturer(manufacturer);
    }

    virtual ~Device(){
        delete [] manufacturer;
    }

    void setManufacturer(const char *manufacturer){
        if (!manufacturer) throw std::invalid_argument("nullptr");
        
        char *temp = new char[strlen(manufacturer) + 1] {};
        strcpy(temp, manufacturer);
        delete [] this->manufacturer;
        
        this->manufacturer = temp;
    }
    const char * getManufacturer() const {
        return manufacturer;
    }

    virtual void print() const {
        std::cout << manufacturer << std::endl;
    } 
    virtual int getPerformance () = 0 const;
    virtual Device* clone() = 0;

private:
    char *manufacturer;
};

class Laptop : public Device {
public:
    Laptop(const char *manufacturer, unsigned clock) : Device(manufacturer), clock(clock){}
    Laptop(const Laptop& other){
        clock = other.clock;
        setManufacturer(other.manufacturer);
    }
    Laptop& operator=(const Laptop& other){
        if(this != &other){
            this->clock = other.clock;
            this->setManufacturer(other.getManufacturer);
        }
        return *this;
    }
    void print() const {
        std::cout << manufacturer << std::endl;
        std::cout << clock << std::endl;
    }
    int getPerformance (){
        return clock;
    }
    
    virtual Laptop* clone(){
        return new Laptop(*this);
    }
private:
    int clock;
}

class Car : public Device {
public:
    Car(const char *manufacturer, unsigned clock) : Device(manufacturer), clock(clock){}
    Car(const Car& other){
        clock = other.clock;
        setManufacturer(other.manufacturer);
    }
    Car& operator=(const Car& other){
        if(this != &other){
            this->clock = other.clock;
            this->setManufacturer(other.getManufacturer);
        }
        return *this;
    }
    void print() const {
        std::cout << manufacturer << std::endl;
        std::cout << power << std::endl;
        std::cout << kubic << std::endl;
    }
    int getPerformance (){
        return power;
    }

    int getPower() const{
        return power;
    }
    int getKubic() const {
        return kubic;
    }

    virtual Car* clone(){
        return new Car(*this);
    }
private:
    int power;
    int kubic;
}

class Inventory{
public:
    Inventory(){
        size = 0;
        maxCap = 100;
    }
    Inventory(const Inventory& other){
        size = other.size;
        maxCap = other.maxCap;
        for(int i = 0; i < size; i++){
            try{
                devices[i] = other.devices[i].clone();
            }catch(...){
                for(int j = 0; j < i; j++)
                    delete devices[i];
                delete [] devices;
                throw;
            }
        }
    }   
    Inventory& operator=(const Inventory& other){
        if(this != &other){
            size = other.size;
            maxCap = other.maxCap;
            for(int i = 0; i < size; i++){
                try{
                    devices[i] = other.devices[i].clone();
                }catch(...){
                    for(int j = 0; j < i; j++)
                        delete devices[i];
                    delete [] devices;
                    throw;
                }
            }    
        }
        return *this;
    }
    ~Inventory(){
        for(int i = 0; i < size; i++){
            delete devices[i];
        }
        delete [] devices;
    }
    Device*[] getDevices (){
        return devices;
    }
    void printAll() const {
        for(int i = 0; i < size; i++){
            std::cout << devices[i]->getManufacturer() << std::endl;
            std::cout << devices[i]->getPerformance() << std::endl;
        }
    }
    bool isSorted() const {
        for(int i = 0; i < size - 1; i++){
            if(devices[i]->getPerformance() > devices[i + 1]->getPerformance())
                return 0;
        }
        return 1;
    }
private:
    unsigned size;
    unsigned maxCap; // 100
    Device* devices[100]; // max
}

int main(){

    return 0;
}