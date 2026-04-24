#include <iostream>
#include <fstream>

// int getSum_t(int i, int j, const int* arr){ // ;)
//     if(!arr || j < 0 || i < 0) return -1;
//     return arr[i] + arr[j];
// }


int getSum(int i, int j){
    std::ifstream file("file.dat", std::ios::in | std::ios::binary);
    
    if(!file.good()){
        std::cout << "No open.." << std::endl;
        return 1;
    }

    file.seekg(0, std::ios::end);
    size_t size = file.tellg() / sizeof(int);

    if(i >= size || j >= size){
        std::cout << "Out of bounds!\n";
        return -1;
    }

    int num1, num2;

    file.seekg(sizeof(int) * i);
    file.read((char* )&num1, sizeof(int));

    file.seekg(sizeof(int) * j);
    file.read((char* )&num2, sizeof(int));

    file.close();

    return num1 + num2;
}


int main(){
    std::ifstream file("file.dat", std::ios::in | std::ios::binary);
   
    if(!file.good()){
        std::cout << "No open.." << std::endl;
        return 1;
    }

    file.seekg(0, std::ios::end);
    size_t size = file.tellg() / sizeof(int);
    std::cout << size;

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
    
    std::cout << "SUM: " << getSum(1, 2) << std::endl;

    delete[] arr;
    file.close();

    std::cout << getSum(1, 3) << std::endl;

    return 0;
}