#include <../lib/ezlib.h>
#include <iostream>

class Student{
    public:
        Student(){
            strcpy_t(mName, (u8*) "Ben 10");
            mYear = 2005;
            mGrade = 6.7;
        }
        bool canGetScolarship(f32 minGrade){
            return mGrade >= minGrade ? true : false;
        }
        u8 getYearInUni(u32 currYear){
            return currYear - 19 - mYear;
        }

        void printStudent(){
            std::cout << "-- Student -- " << std::endl;
            std::cout << "Name: " << mName << std::endl;
            std::cout << "Birth Year: " << mYear << std::endl;
            std::cout << "Grade: " << mGrade << std::endl;
        }
        void setName(u8 *name) {
            if(!name) return;
            if(strlen_t(name) >= 32) return;
            strcpy_t(mName, name);
        }
        void setYear(u32 year) {mYear = year;} 
        void setGrade(f32 grade) {mGrade = grade;}
        const u8* getName() const {return mName;}
        const u32 getYear() const {return mYear;} 
        const f32 getGrade() const {return mGrade;}
    private:
        u32 mYear;  //birthYear
        f32 mGrade;
        u8 mName[32];
};

int main(){
    
    return 0;
}