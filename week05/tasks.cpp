#include <iostream>

template <typename T>
T sum(const T a, const T b){
    return a + b;
}

template <typename S>
void swap(S a, S b){
    *a ^= *b; 
    *b = *a ^ *b;
    *a ^= *b;
}

template <typename A>
void printArr(const A arr, const size_t size){
    for(int i = 0; i < size; i++)
        std::cout << arr[i] << " ";
}
template<>
void printArr(const char *arr, const size_t size){
    for(int i = 0; i < size; i++)
        std::cout << arr[i] << " ";
}

template <typename B, typename C, typename D>
void printRand(B a, C b, D c){
    std::cout << a << b << c << std::endl;
}

template <typename E>
bool arrIncludes(const E *arr, const E x, const size_t size){
    for(int i = 0; i < size; i++){
        if(arr[i] == x) return true;
    }
    return false;
}

template <typename U>
void map(U *&arr, const size_t size, U (*pred)(U)){
    if (!arr || !pred) return;
	for(size_t i = 0; i < size; i++)
        arr[i] = pred(arr[i]);
}

template <typename V>
V *filter(const V* arr, bool (*pred)(V), V& newSize, const size_t size){
    if (!arr || !pred) return nullptr;
	for (int i = 0; i < size; i++){
		if (pred(arr[i])) newSize++;
	}

	V* newArr = new (std::nothrow) V[newSize];
    if (!newArr) return nullptr;
    
    for (V i = 0, j = 0; i < size; i++){
		if (pred(arr[i])) newArr[j++] = arr[i];
	}
    
    return newArr;
}

template <typename F>
F fold(const F* arr, const size_t size, F n, F (*f)(F, F)){
	if (!arr || !f) return 0;
	int sum = n;
	for (int i = 0; i < size; i++)
		sum = f(sum, arr[i]);
	return sum;
}

int addTen(int a){
    return a + 10;
}

int main(){
    int a = 5, b = 6;

    swap(&a, &b);

    std::cout << a << " : " << b << std::endl;
    std::cout << sum(1, 2) << std::endl;

    int arr[] = {1, 2, 3};

    std::cout << arrIncludes(arr, 3, 3) << std::endl; 
    std::cout << arrIncludes(arr, 4, 3) << std::endl; 

    int *arr2 = new int[3];
    for(int i = 0; i < 3; i ++)
        arr2[i] = i;

    // map(arr2, 3, [](int a){
    //     return a * 10;
    // });

    map(arr2, 3, addTen);
    printArr(arr2, 3);


    std::cout << std::endl;
    return 0;   
}
