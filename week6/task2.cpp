#include "../lib/ezlib.h"
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
            return mMonth > 6 && mMonth < 10;
        }
        
        void setDay(const u16 day) {
            if(day > 12) return;
            mDay = day;
        }
        void setMonth(const u16 month) {
            if(month > 12) return;
            mMonth = month;
        } 
        void setYear(const u32 year) {mYear = year;}

        u16 getDay()   const {return mDay;}
        u16 getMonth() const {return mMonth;} 
        u32 getYear() const {return mYear;}
    private:
        u32 mYear;  //birthYear
        u16  mDay;
        u16  mMonth;
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
            return mHour > 0 && mHour < 6; // mejdu 0 i 6 che lowk do 12 si e obqd
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
                mMinute = 0;
            }
            else mMinute++;
        }
        void passHour(){
            if(mHour >= 23) mHour = 0;
            else mHour++;
        }

        void setSecond(const u16 sec) {
            if(sec > 59) throw std::invalid_argument("Seconds can't be more than 59");
            mSec = sec;
        }
        void setMinute(const u16 minute) {
            if(minute > 59) throw std::invalid_argument("Minutes can't be more than 59");
            mMinute = minute;
        } 
        void setHour(const u16 hour) {
            if(hour > 23) throw std::invalid_argument("Hours can't be more than 24");;
            mHour = hour;
        }

        u16 getSecond() const {return mSec;}
        u16 getMinute() const {return mMinute;} 
        u16 getHour()  const {return mHour;}
    private:
        u16  mHour;
        u16  mSec;
        u16  mMinute;
};

int main(){
    Date date;
    date.setDay(30);
    date.setMonth(6);
    date.setYear(2026);
    std::cout << "Initial date:" << std::endl;
    date.printDate();

    date.passDay();
    std::cout << "After passDay:" << std::endl;
    date.printDate();
    std::cout << "Is summer vacation: " << date.isSummerVacation() << std::endl;

    Time time;
    time.setHour(23);
    time.setMinute(59);
    time.setSecond(58);
    std::cout << "\nInitial time: ";
    time.printTime();

    time.passSecond();
    time.passSecond();
    std::cout << "After 2 seconds: ";
    time.printTime();
    std::cout << "Is night: " << time.isNight() << std::endl;

    return 0;
}