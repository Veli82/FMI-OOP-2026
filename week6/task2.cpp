#include <../lib/ezlib.h>
#include <iostream>

class Date{
    public:
        Date(){
            mDay = 6;
            mMonth = 7;
            mYear = 6767;
        }

        void printDate(){
            std::cout << "-- Date -- " << std::endl;
            std::cout << "Day: " << mDay << std::endl;
            std::cout << "Month: " << mMonth << std::endl;
            std::cout << "Year: " << mYear << std::endl;
        }

        void passDay(){
            if(mDay >= 30){
                passMonth();
                mDay = 1;
            }
            else mDay++;
        }
        void passMonth(){
            if(mMonth >= 12){
                passYear();
                mMonth = 1;
            }    
            else mMonth++;
        }
        void passYear(){
            mYear++;
        }
        bool isSummerVacation(){
            return mMonth > 6 && mMonth < 10 ? true : false;
        }
        
        void setDay(u8 day) {
            if(day > 12) return;
            mDay = day;
        }
        void setMonth(u8 month) {
            if(month > 12) return;
            mMonth = month;
        } 
        void setYear(u32 year) {mYear = year;}

        const u8 getDay()   const {return mDay;}
        const u8 getMonth() const {return mMonth;} 
        const u32 getYear() const {return mYear;}
    private:
        u32 mYear;  //birthYear
        u8  mDay;
        u8  mMonth;
};

class Time{
    public:
        Time(){
            mSec = 39;
            mMinute = 12;
            mHour = 10;
        }

        void printTime(){
            std::cout << mHour << ":" << mMinute << ":" << mSec << std::endl;
        }
        bool isNight(){
            return mHour > 0 && mHour < 6 ? true : false; // mejdu 0 i 6 che lowk do 12 si e obqd
        }

        void passSecond(){
            if(mSec >= 59){
                passMinute();
                mSec = 0;
            }
            else mSec++;
        }
        void passMinute(){
            if(mMinute >= 59){
                passHour();
                mMinute = 1;
            }    
            else mMinute++;
        }
        void passHour(){
            if(mHour >= 23)
                mHour = 0;
            mHour++;
        }

        void setSecond(u8 sec) {
            if(sec > 59) return;
            mSec = sec;
        }
        void setMinute(u8 minute) {
            if(minute > 59) return;
            mMinute = minute;
        } 
        void setHour(u8 hour) {
            if(hour > 23) return;
            mHour = hour;
        }

        const u8 getSecond() const {return mSec;}
        const u8 getMinute() const {return mMinute;} 
        const u8 getHour()  const {return mHour;}
    private:
        u8  mHour;
        u8  mSec;
        u8  mMinute;
};

int main(){

    return 0;
}