#include <iostream>
#include <fstream>

struct Student
{
    char name[32];
	unsigned year;
	float grade;
};

int main(){
    int n;
    
    std::cin >> n;
    std::ofstream oFile("students.dat", std::ios::out | std::ios::binary);
   
    for(int i = 0; i < n; i++){
        Student p;

        p.grade = 6.7;
        strcpy(p.name, "sixSeven");
        p.year = i;

        oFile.write((const char*) &p, sizeof(Student));
    }

    oFile.close();
    std::ifstream iFile("students.dat", std::ios::in | std::ios::binary);

    Student* arr = new Student[n];
    for(int i = 0; i < n; i++){
        iFile.read((char*) &arr[i], sizeof(Student));
        std::cout << arr[i].year << " ";
    }
    
    std::cout << '\n';

    delete[] arr;
    iFile.close();

    // std::cout << sizeof(unsigned) << std::endl << sizeof(float) << '\n';
    
    return 0;
}