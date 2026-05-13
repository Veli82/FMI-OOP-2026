#include <iostream>
#include <cstring>

class TEST {
    public:
        TEST() : name(nullptr){
        }

        TEST(const TEST& other) {
        }

        TEST& operator=(const TEST& other) {
            if (this != &other) {
            }
            return *this;
        }

        ~TEST() {
            std::cout << "test";
        }

        void setName(const char *name){
            if(!name) throw std::invalid_argument("asd");
            
            size_t len = strlen(name);
            char *temp = new char[len + 1]{};

            delete [] this->name;
            this->name = temp;
        }
        
    private:
        char *name;
};

int main(){
    TEST test;

    test.setName("asdsdds");
    test.setName(nullptr);

    std::cout << "end";

    return 0;
}