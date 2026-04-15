#include <iostream>
#include "../lib/ezlib.h"

class Phone{
    public:
        Phone() : mModel(nullptr), mOsVersion(0), mBattery(0), mVolume(0) {
            setBattery(100);
            setVolume(10);
            mOsVersion = 67;
            setModel("Iphone 67");
        }

        Phone(
            unsigned short battery,
            unsigned short volume,
            unsigned int osVersion,
            const char *model
        ) : mModel(nullptr), mOsVersion(0), mBattery(0), mVolume(0) {
            setBattery(battery);
            setVolume(volume);
            mOsVersion = osVersion;
            setModel(model);
        }

        void printPhone(){
            std::cout << "-- Phone --";
            std::cout << "Model : " << mModel; 
            std::cout << "Battery : " << mBattery; 
            std::cout << "Volume : " << mVolume; 
            std::cout << "OsVer : " << mOsVersion; 
        }

        void watchReels(int min){
            while(hasBattery() && min-- > 0)
                consumeBattery(1);
        }
        void playClash(int min){
            while(hasBattery() && min-- > 0)
                consumeBattery(3);
        }
        void takePhoto(){if(hasBattery()) consumeBattery(1);}
        void charge(int min){
            if(min <= 0) return;

            const unsigned int charged = (unsigned int)mBattery + (unsigned int)min;
            mBattery = charged > 100 ? 100 : (unsigned short)charged;
        }

        void update() {
            if(hasBattery()) this->mOsVersion++;
        }

        void setVolume(unsigned short volume) {
            if(volume > 10) throw std::invalid_argument("Volume should be 0-10");
            mVolume = volume;
        }
        void setModel(const char *model) {
            if(!model) throw std::invalid_argument("Model can't be null");

            const size_t len = strlen_t(model);
            char* newModel = new (std::nothrow) char[len + 1];
            if(!newModel) throw std::bad_alloc();

            strcpy_t(newModel, model);

            delete[] mModel;
            mModel = newModel;
        }
        
        unsigned short getBattery() const {return mBattery;}
        unsigned short getVolume() const {return mVolume;}
        unsigned int getOsVersion() const {return mOsVersion;}
        const char *getModel() const {return mModel;}

        ~Phone(){clear();}
    private:
        bool hasBattery(){
            return mBattery > 0;
        }
        void setBattery(unsigned short battery){
            if(battery > 100) throw std::invalid_argument("Battery should be 0-100");
            mBattery = battery;
        }
        void consumeBattery(unsigned short amount){
            if(amount >= mBattery) {
                mBattery = 0;
                return;
            }
            mBattery -= amount;
        }

        void clear(){
            delete[] mModel;
            mModel = nullptr;
            mBattery = 0;
            mVolume = 0;
            mOsVersion = 0;
        }

        char *mModel;                       // -- 8  
        unsigned int mOsVersion;            // -- 4
        unsigned short mBattery; // 0 - 100 // -- 2
        unsigned short mVolume; // 0 - 10   // -- 2
};
 
int main(void){
    
    return 0;
}