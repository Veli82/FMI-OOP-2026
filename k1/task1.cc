#include <iostream>
#include <stdexcept>
#include <utility>
#include <fstream>

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

    ~ElectricDevice(){
        delete [] desc;
        delete [] brand;
    }
    void turnOn(){
        if(isPlugged) isOn = true;
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
std::ostream& operator <<(std::ostream& o, const ElectricDevice& device){
    o << "ElectricDevice:" << std::endl;
    o << "br: " << device.getBrand() << std::endl;
    o << "desc: " << device.getDesc() << std::endl;
    o << "ison: " << device.getIsOn() << std::endl;
    o << "isplug: " << device.getIsPlugged() << std::endl;
    o << "power: " << device.getPower() << std::endl;
    o << "sn: " << device.getSerialNum() << std::endl;

    return o;
}


class Splitter{
    public:
        Splitter()
            : devices(nullptr), size(0), capacity(0), maxPower(0) {}

        Splitter(size_t capacity, size_t maxPower)
            : devices(nullptr), size(0), capacity(capacity), maxPower(maxPower) {
            if(capacity > 0){
                devices = new ElectricDevice[capacity];
            }
        }

        Splitter(const Splitter& other)
            : devices(nullptr), size(other.size), capacity(other.capacity), maxPower(other.maxPower) {
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
            swap(lhs.maxPower, rhs.maxPower);
        }

        Splitter& operator=(Splitter other){
            swap(*this, other);
            return *this;
        }

        ~Splitter(){
            delete [] devices;
        }

        void addDevice(const ElectricDevice& device){
            // if(size >= capacity && totalPowerConsumption() + device.getPower() > maxPower)
            if(size >= capacity)
                return;

            devices[size++] = device;

            if(totalPowerConsumption() > maxPower) die();
        }
        void removeLastDevice(){ // ne se kazva che trqbva specifichno
            if(size == 0) return;
            size--;
        }
        void die(){
            size = 0;
            capacity = 0;
            maxPower = 0;
            delete [ ] devices;
            devices = nullptr;
        }


        const ElectricDevice *getDevices() const {
            return devices;
        }
        size_t getSize() const {
            return size;
        }
        size_t getCapacity() const {
            return capacity;
        }
        size_t getMaxPower() const {
            return maxPower;
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
    private:
        ElectricDevice *devices;
        size_t size;
        size_t capacity;

        size_t maxPower; // max usage
};

std::ostream& operator <<(std::ostream& o, const Splitter& splitter){
    o << "Splitter:" << std::endl;
    o << "cap:" << splitter.getCapacity() << std::endl;
    o << "currturn:" << splitter.getSize() << std::endl;
    o << "maxpower:" << splitter.getMaxPower() << std::endl;

    for(size_t i = 0; i < splitter.getSize(); i++){
        o << "Device[" << i << "]: " << splitter.getDevices()[i] << std::endl;
    }

    return o;
}

int main(){
    int N = 0, I = 0;
    
    char *textName = new (std::nothrow) char[100];
    if(!textName) return 1;
    
    std::cin >> N >> I;
    Splitter spl(N, I);
    
    std::cin >> textName;
    std::ifstream file(textName, std::ios::in);
    if(!file) {std::cout << "wtf\n"; return -1;}
    
    char *desc = new (std::nothrow) char[100];
    if(!desc) {delete [] textName; return 1;}

    char *brand = new (std::nothrow) char[100];
    if(!brand) {delete [] textName; delete [] desc; return 1;}

    size_t power = 0;
    bool isPlugged = false; 
    bool isOn = false;

    file >> desc >> brand >> power >> isPlugged >> isOn;

    ElectricDevice dishWasher(desc, brand, power, isPlugged, isOn);

    spl.addDevice(dishWasher);
    std::cout << spl;

    return 0;
}