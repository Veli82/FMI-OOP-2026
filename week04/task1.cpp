#include <iostream>
#include <fstream>

int main(){
    int n;
    
    std::cin >> n;
    std::ofstream file("numbers.dat", std::ios::out | std::ios::binary);
   
    if(!file.good()){
        std::cout << "No open.." << std::endl;
        return 1;
    }

    int* arr = new (std::nothrow) int[n];
    if(!arr){
        std::cout << "No malloc.." << std::endl;
        return 1;
    }

    for(int i = 0; i < n; i++)
        std::cin >> arr[i];
    
    file.write((const char*) &n, sizeof(int));
    file.write((const char*) arr, n * sizeof(int));

    delete[] arr;
    file.close();

    return 0;
}