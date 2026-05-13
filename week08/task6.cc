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

class Sticker {
public:
    Sticker()
        : Sticker("FMI") {
    }

    Sticker(const char* university)
        : id(nextId++), university(nullptr), remainingMeals(2), owner(nullptr) {
        setUniversity(university);
    }

    Sticker(const Sticker& other)
        : id(nextId++), university(nullptr), remainingMeals(other.remainingMeals), owner(nullptr) {
        setUniversity(other.university);
    }

    Sticker& operator=(const Sticker& other) {
        if (this != &other) {
            setUniversity(other.university);
            remainingMeals = other.remainingMeals;
        }
        return *this;
    }

    ~Sticker() {
        delete[] university;
    }

    unsigned getId() const {
        return id;
    }

    const char* getUniversity() const {
        return university;
    }

    unsigned getRemainingMeals() const {
        return remainingMeals;
    }

    Student* getOwner() const {
        return owner;
    }

    void setUniversity(const char* newUniversity) {
        char* copy = duplicateText(newUniversity);
        delete[] university;
        university = copy;
    }

    void resetMeals() {
        remainingMeals = 2;
    }

    void consumeMeal() {
        if (remainingMeals == 0) {
            throw std::runtime_error("no meals left");
        }

        --remainingMeals;
    }

    void printInfo() const {
        std::cout << "Sticker id: " << id << '\n';
        std::cout << "University: " << university << '\n';
        std::cout << "Remaining meals: " << remainingMeals << '\n';
    }

private:
    friend class Student;

    void setOwner(Student* newOwner) {
        owner = newOwner;
    }

    static unsigned nextId;

    const unsigned id;
    char* university;
    unsigned remainingMeals;
    Student* owner;
};

class Student {
public:
    Student()
        : Student("Ben 10") {
    }

    Student(const char* name)
        : name(nullptr), sticker(nullptr) {
        setName(name);
    }

    Student(const Student& other)
        : name(nullptr), sticker(nullptr) {
        setName(other.name);
    }

    Student& operator=(const Student& other) {
        if (this != &other) {
            setName(other.name);
        }
        return *this;
    }

    ~Student() {
        delete sticker;
        delete[] name;
    }

    const char* getName() const {
        return name;
    }

    Sticker* getSticker() const {
        return sticker;
    }

    void setName(const char* newName) {
        char* copy = duplicateText(newName);
        delete[] name;
        name = copy;
    }

    void issueSticker(const char* university) {
        Sticker* newSticker = new Sticker(university);
        newSticker->setOwner(this);

        delete sticker;
        sticker = newSticker;
    }

    void getFood() {
        if (sticker == nullptr) {
            throw std::runtime_error("no sticker");
        }

        sticker->consumeMeal();
    }

    void printInfo() const {
        std::cout << "Student: " << name << '\n';
        if (sticker != nullptr) {
            sticker->printInfo();
        } else {
            std::cout << "No sticker\n";
        }
    }

private:
    char* name;
    Sticker* sticker;
};

unsigned Sticker::nextId = 0;

int main() {
    try {
        Student student("Marto");
        student.issueSticker("FMI");
        student.printInfo();

        student.getFood();
        student.getFood();
        student.printInfo();

        try {
            student.getFood();
        } catch (const std::exception& ex) {
            std::cout << "Expected error: " << ex.what() << '\n';
        }

        student.issueSticker("SU");
        std::cout << "After issuing new sticker:\n";
        student.printInfo();
    } catch (const std::exception& ex) {
        std::cout << "Error: " << ex.what() << '\n';
    }

    return 0;
}
