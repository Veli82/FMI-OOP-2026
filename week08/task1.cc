#include <iostream>
#include "../lib/ezlib.h"

class Student{
    public:
        Student(){
            setName("Ben 10");
            mYear = 2005;
            mGrade = 6.7;
            id++;
        }
        Student(const char* name, unsigned int year, float grade){
            setName(name);
            mYear = year;
            mGrade = grade;
            id++;
        }
        Student (const Student& other){
            setName(other.mName);
            mYear = other.mYear;
            mGrade = other.mGrade;
            id++;
        }
        Student& operator=(const Student& other){
            if(this == &other) return *this;
            
            setName(other.mName);
            mYear = other.mYear;
            mGrade = other.mGrade;

            return *this;
        }
        ~Student(){
            delete [] mName;
        }

        bool canGetScolarship(float minGrade){
            return mGrade >= minGrade;
        }
        char getYearInUni(unsigned int currYear){
            return currYear - 19 - mYear;
        }

        void printStudent(){
            std::cout << "-- Student -- " << std::endl;
            std::cout << "Name: " << mName << std::endl;
            std::cout << "Birth Year: " << mYear << std::endl;
            std::cout << "Grade: " << mGrade << std::endl;
        }
        void setName(const char *name) {
            if(!name) throw std::invalid_argument("Name can't be empty");
            
            delete [] mName;
            mName = new char[strlen_t(name)];

            strcpy_t(mName, name);
        }
        void setYear(unsigned int year) {mYear = year;} //validaciq mrz me pls
        void setGrade(float grade) {mGrade = grade;} //validaciq
        const char* getName() const {return mName;}
        unsigned int getYear() const {return mYear;} 
        float getGrade() const {return mGrade;}
        static unsigned int getId() {return id;}
    private:
        static unsigned int id;
        unsigned int mYear;  //birthYear
        float mGrade;
        char *mName;
};

int main(void){
    
    return 0;
}