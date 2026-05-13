#include <iostream>
#include <fstream>

int main(){
    std::ifstream file("numbers.dat", std::ios::in | std::ios::binary);
   
    if(!file.good()){
        std::cout << "No open.." << std::endl;
        return 1;
    }

    file.seekg(0, std::ios::end);
    size_t size = file.tellg() / sizeof(int);

    int* arr = new (std::nothrow) int[size];
    if(!arr){
        std::cout << "No malloc.." << std::endl;
        return 1;
    }

    file.seekg(0);

    for(int i = 0; i < size; i++)
        file.read((char* )&arr[i], sizeof(int));

    for(int i = 0; i < size; i++)
        std::cout << arr[i] << " ";
    
    std::cout << std::endl;

    delete[] arr;
    file.close();

    return 0;
}