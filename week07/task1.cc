#include <iostream>
#include "../lib/ezlib.h"

class Student{
    public:
        Student() : mYear(0), mGrade(0.0f), mName(nullptr) {
            setName("Ben 10");
            setYear(2005);
            setGrade(5.7f);
        }
        Student(const char* name, unsigned int year, float grade) : mYear(0), mGrade(0.0f), mName(nullptr) {
            setName(name);
            setYear(year);
            setGrade(grade);
        }
        Student (const Student& other) : mYear(0), mGrade(0.0f), mName(nullptr) {
            setName(other.mName);
            setYear(other.mYear);
            setGrade(other.mGrade);
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
            const size_t len = strlen_t(name);

            char* newName = new (std::nothrow) char[len + 1];
            if(!newName) throw std::bad_alloc();

            strcpy_t(newName, name);

            delete [] mName;
            mName = newName;
        }
        void setYear(unsigned int year) {
            if(year < 1900 || year > 2100)
                throw std::invalid_argument("Year should be in [1900, 2100]");
            mYear = year;
        }
        void setGrade(float grade) {
            if(grade < 2.0f || grade > 6.0f)
                throw std::invalid_argument("Grade should be in [2.0, 6.0]");
            mGrade = grade;
        }
        const char* getName() const {return mName;}
        unsigned int getYear() const {return mYear;} 
        float getGrade() const {return mGrade;}
    private:
        unsigned int mYear;  //birthYear
        float mGrade;
        char *mName;
};

int main(void){
    
    return 0;
}