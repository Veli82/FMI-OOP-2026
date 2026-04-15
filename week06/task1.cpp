#include "../lib/ezlib.h"
#include <iostream>

class Student{
    public:
        Student(){
            strcpy_t(mName, (u8*) "Ben 10");
            mYear = 2005;
            mGrade = 6.7;
        }
        bool canGetScolarship(const f32 minGrade){
            return mGrade >= minGrade;
        }
        u8 getYearInUni(const u32 currYear){
            return currYear - 19 - mYear;
        }

        void printStudent(){
            std::cout << "-- Student -- " << std::endl;
            std::cout << "Name: " << mName << std::endl;
            std::cout << "Birth Year: " << mYear << std::endl;
            std::cout << "Grade: " << mGrade << std::endl;
        }
        void setName(const u8 *name) {
            if(!name) throw std::invalid_argument("Name can't be empty");
            if(strlen_t(name) >= 32) throw std::invalid_argument("Name len (1-32)");
            strcpy_t(mName, name);
        }
        void setYear(const u32 year) {mYear = year;} 
        void setGrade(const f32 grade) {mGrade = grade;}
        const u8* getName() const {return mName;}
        u32 getYear() const {return mYear;} 
        f32 getGrade() const {return mGrade;}
    private:
        u32 mYear;  //birthYear
        f32 mGrade;
        u8 mName[32];
};

int main(){
    Student s;
    s.printStudent();

    s.setName((u8*) "Valentin");
    s.setYear(2004);
    s.setGrade(5.75f);

    std::cout << "\nAfter updates:" << std::endl;
    s.printStudent();

    std::cout << "Scholarship (>= 5.50): " << s.canGetScolarship(5.50f) << std::endl;
    std::cout << "Year in uni (2026): " << static_cast<int>(s.getYearInUni(2026)) << std::endl;

    return 0;
}