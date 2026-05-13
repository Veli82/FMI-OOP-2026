#include <iostream>
#include <stdexcept>
#include <utility>

size_t strlen_t(const char *str){
    if(!str) throw std::invalid_argument("No null strings");
    size_t len = 0;
    for(; str[len] != '\0'; len++);
    
    return len;
}

void strcpy_t(char *&dest, const char *src){
    if(!src) throw std::invalid_argument("No null strings");

    char *newStr = new char[strlen_t(src) + 1];
    size_t len = strlen_t(src);
    for(size_t i = 0; i < len; i++){
        newStr[i] = src[i];
    }
    newStr[len] = '\0';

    delete [] dest;
    dest = newStr;
}

class ElectricDevice{
public:
    ElectricDevice()
        : desc(nullptr), brand(nullptr), power(0), isPlugged(false), isOn(false), serialNum(nextSerialNum++) {
        setDesc("Unknown device");
        setBrand("Unknown brand");
    }

    ElectricDevice(const char *desc, const char *brand, size_t power, bool isPlugged, bool isOn)
        : desc(nullptr), brand(nullptr), power(power), isPlugged(isPlugged), isOn(isOn), serialNum(nextSerialNum++) {
        setDesc(desc);
        setBrand(brand);
    }

    ElectricDevice(const ElectricDevice& other)
        : desc(nullptr), brand(nullptr), power(other.power), isPlugged(other.isPlugged), isOn(other.isOn), serialNum(other.serialNum) {
        setDesc(other.desc);
        setBrand(other.brand);
    }

    friend void swap(ElectricDevice& lhs, ElectricDevice& rhs) noexcept {
        using std::swap;
        swap(lhs.desc, rhs.desc);
        swap(lhs.brand, rhs.brand);
        swap(lhs.power, rhs.power);
        swap(lhs.isPlugged, rhs.isPlugged);
        swap(lhs.isOn, rhs.isOn);
        swap(lhs.serialNum, rhs.serialNum);
    }

    ElectricDevice& operator=(ElectricDevice other){
        swap(*this, other);
        return *this;
    }

    void turnOn(){
        if(isPlugged){
            isOn = true;
        }
    }
    void turnOff(){
        isOn = false;
    }
    void plugIn(){
        isPlugged = true;
    }
    void unplug(){
        isPlugged = false;
        isOn = false;
    }
    ~ElectricDevice(){
        delete [] desc;
        delete [] brand;
    }

    const char *getDesc() const {
        return desc;
    }; 
    const char *getBrand() const {
        return brand;
    };
    size_t getPower() const {
        return power;
    };
    bool getIsPlugged() const {
        return isPlugged;
    }; 
    bool getIsOn() const {
        return isOn;
    };
    size_t getSerialNum() const {
        return serialNum;
    };

    void setDesc(const char *desc)  {
        strcpy_t(this->desc, desc);
    }; 
    void setBrand(const char *brand)  {
        strcpy_t(this->brand, brand);
    };
    void setPower(size_t power)  {
        this->power = power;
    };
    void setIsPlugged(bool isPlugged)  {
        this->isPlugged = isPlugged;
    }; 
    void setIsOn(bool isOn)  {
        this->isOn = isOn;
    };

    private:
        char *desc;    // not null
        char *brand;   // not null
        size_t power;  // amps
        bool isPlugged; 
        bool isOn;

        size_t serialNum; // const after creation
        static size_t nextSerialNum;
};

size_t ElectricDevice::nextSerialNum = 1;

class Splitter{
    public:
        Splitter()
            : devices(nullptr), size(0), capacity(0) {}

        Splitter(size_t capacity)
            : devices(nullptr), size(0), capacity(capacity) {
            if(capacity > 0){
                devices = new ElectricDevice[capacity];
            }
        }

        Splitter(const Splitter& other)
            : devices(nullptr), size(other.size), capacity(other.capacity) {
            if(capacity > 0){
                devices = new ElectricDevice[capacity];
                for(size_t i = 0; i < size; i++){
                    devices[i] = other.devices[i];
                }
            }
        }

        friend void swap(Splitter& lhs, Splitter& rhs) noexcept {
            using std::swap;
            swap(lhs.devices, rhs.devices);
            swap(lhs.size, rhs.size);
            swap(lhs.capacity, rhs.capacity);
        }

        Splitter& operator=(Splitter other){
            swap(*this, other);
            return *this;
        }

        ~Splitter(){
            delete [] devices;
        }

        bool addDevice(const ElectricDevice& device){
            if(size >= capacity)
                return false;

            devices[size++] = device;
            return true;
        }

        bool removeLastDevice(){
            if(size == 0)
                return false;

            size--;
            return true;
        }

        size_t getSize() const {
            return size;
        }
        size_t getCapacity() const {
            return capacity;
        }
        size_t totalPowerConsumption() const {
            size_t total = 0;
            for(size_t i = 0; i < size; i++){
                if(devices[i].getIsOn()){
                    total += devices[i].getPower();
                }
            }

            return total;
        }
    private: // vector
        ElectricDevice *devices;
        size_t size;
        size_t capacity;
};

int main(){
    int N, I;

    std::cin >> N >> I;

    

    return 0;
}