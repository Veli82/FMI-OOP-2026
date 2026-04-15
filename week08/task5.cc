#include <cstring>
#include <iostream>
#include <stdexcept>

class Student;

char* duplicateText(const char* text) {
    if (!text) {
        throw std::invalid_argument("null text");
    }

    size_t length = std::strlen(text);
    char* copy = new char[length + 1];
    std::strcpy(copy, text);
    return copy;
}

class Car {
public:
    Car()
        : horsepower(0), owner(nullptr) {
        setModel("Generic");
        setHorsepower(100);
    }

    Car(const char* model, unsigned horsepower)
        : horsepower(0), owner(nullptr) {
        setModel(model);
        setHorsepower(horsepower);
    }

    Car(const Car& other)
        : horsepower(other.horsepower), owner(nullptr) {
        setModel(other.model);
    }

    Car& operator=(const Car& other) {
        if (this != &other) {
            setModel(other.model);
            horsepower = other.horsepower;
        }
        return *this;
    }

    const char* getModel() const {
        return model;
    }

    unsigned getHorsepower() const {
        return horsepower;
    }

    Student* getOwner() const {
        return owner;
    }

    void setModel(const char* newModel) {
        size_t length = std::strlen(newModel);
        if (length > 32) {
            throw std::runtime_error("model too long");
        }

        std::strcpy(model, newModel);
    }

    void setHorsepower(unsigned newHorsepower) {
        if (newHorsepower == 0) {
            throw std::runtime_error("invalid horsepower");
        }

        horsepower = newHorsepower;
    }

    void printInfo() const {
        std::cout << "Car: " << model << " | " << horsepower << " hp | ";
        if (owner != nullptr) {
            std::cout << "has owner";
        } else {
            std::cout << "no owner";
        }
        std::cout << '\n';
    }

private:
    friend class Student;

    void setOwner(Student* newOwner) {
        owner = newOwner;
    }

    char model[33]{};
    unsigned horsepower;
    Student* owner;
};

class Student {
public:
    Student()
        : Student("Ben 10") {
    }

    Student(const char* name)
        : id(nextId++), name(nullptr), personalCar(nullptr) {
        setName(name);
    }

    Student(const Student& other)
        : id(nextId++), name(nullptr), personalCar(nullptr) {
        setName(other.name);
    }

    Student& operator=(const Student& other) {
        if (this != &other) {
            setName(other.name);
        }
        return *this;
    }

    ~Student() {
        if (personalCar != nullptr) {
            personalCar->setOwner(nullptr);
        }
        delete[] name;
    }

    unsigned getId() const {
        return id;
    }

    const char* getName() const {
        return name;
    }

    Car* getPersonalCar() const {
        return personalCar;
    }

    void setName(const char* newName) {
        char* copy = duplicateText(newName);
        delete[] name;
        name = copy;
    }

    void setPersonalCar(Car* newCar) {
        if (personalCar == newCar) {
            return;
        }

        if (personalCar != nullptr) {
            personalCar->setOwner(nullptr);
        }

        if (newCar != nullptr && newCar->owner != nullptr) {
            newCar->owner->personalCar = nullptr;
        }

        personalCar = newCar;

        if (personalCar != nullptr) {
            personalCar->setOwner(this);
        }
    }

    void printInfo() const {
        std::cout << "Student " << name << " (id " << id << ")\n";
        if (personalCar != nullptr) {
            personalCar->printInfo();
        } else {
            std::cout << "No car\n";
        }
    }

private:
    static unsigned nextId;

    const unsigned id;
    char* name;
    Car* personalCar;
};

unsigned Student::nextId = 0;

int main() {
    try {
        Student s1("Pesho");
        Student s2("Gosho");
        Car c1("BMW M3", 480);

        s1.setPersonalCar(&c1);
        std::cout << "After assigning to Pesho:\n";
        s1.printInfo();
        s2.printInfo();

        s2.setPersonalCar(&c1);
        std::cout << "After transferring to Gosho:\n";
        s1.printInfo();
        s2.printInfo();
    } catch (const std::exception& ex) {
        std::cout << "Error: " << ex.what() << '\n';
    }

    return 0;
}
