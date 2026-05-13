#include <cstring>
#include <iostream>
#include <stdexcept>

class Obshtak;

char* duplicateText(const char* text) {
    if (!text) {
        throw std::invalid_argument("null text");
    }

    size_t length = std::strlen(text);
    char* copy = new char[length + 1];
    std::strcpy(copy, text);
    return copy;
}

class Student {
public:
    Student();
    Student(const char* name, unsigned year, float grade);
    Student(const Student& other);
    Student& operator=(const Student& other);
    ~Student();

    unsigned getId() const;
    const char* getName() const;
    unsigned getYear() const;
    float getGrade() const;
    Obshtak* getObshtak() const;

    void setName(const char* newName);
    void setYear(unsigned newYear);
    void setGrade(float newGrade);
    void leaveObshtak();
    void printStudent() const;

private:
    friend class Obshtak;

    void setObshtak(Obshtak* newObshtak);

    static unsigned nextId;

    const unsigned id;
    char* name;
    unsigned year;
    float grade;
    Obshtak* obshtak;
};

class Obshtak {
public:
    Obshtak();
    Obshtak(int roomNum, int blockNum);
    Obshtak(const Obshtak& other);
    Obshtak& operator=(const Obshtak& other);
    ~Obshtak();

    int getRoomNum() const;
    int getBlockNum() const;

    void setRoomNum(int newRoomNum);
    void setBlockNum(int newBlockNum);

    bool hasRoom() const;
    void addStudent(Student& student);
    void evictStudentById(unsigned studentId);
    void printInfo() const;

private:
    void clearResidents();

    int roomNum;
    int blockNum;
    Student* students[3];
    size_t count;
};

unsigned Student::nextId = 0;

Student::Student()
    : Student("Ben 10", 2005, 6.7f) {
}

Student::Student(const char* name, unsigned year, float grade)
    : id(nextId++), name(nullptr), year(year), grade(grade), obshtak(nullptr) {
    setName(name);
}

Student::Student(const Student& other)
    : id(nextId++), name(nullptr), year(other.year), grade(other.grade), obshtak(nullptr) {
    setName(other.name);
}

Student& Student::operator=(const Student& other) {
    if (this != &other) {
        setName(other.name);
        year = other.year;
        grade = other.grade;
    }
    return *this;
}

Student::~Student() {
    delete[] name;
}

unsigned Student::getId() const {
    return id;
}

const char* Student::getName() const {
    return name;
}

unsigned Student::getYear() const {
    return year;
}

float Student::getGrade() const {
    return grade;
}

Obshtak* Student::getObshtak() const {
    return obshtak;
}

void Student::setName(const char* newName) {
    char* copy = duplicateText(newName);
    delete[] name;
    name = copy;
}

void Student::setYear(unsigned newYear) {
    year = newYear;
}

void Student::setGrade(float newGrade) {
    grade = newGrade;
}

void Student::setObshtak(Obshtak* newObshtak) {
    obshtak = newObshtak;
}

void Student::leaveObshtak() {
    if (obshtak != nullptr) {
        obshtak->evictStudentById(id);
    }
}

void Student::printStudent() const {
    std::cout << "-- Student --\n";
    std::cout << "ID: " << id << '\n';
    std::cout << "Name: " << name << '\n';
    std::cout << "Year: " << year << '\n';
    std::cout << "Grade: " << grade << '\n';
}

Obshtak::Obshtak()
    : roomNum(0), blockNum(0), count(0) {
    for (size_t index = 0; index < 3; ++index) {
        students[index] = nullptr;
    }
}

Obshtak::Obshtak(int roomNum, int blockNum)
    : roomNum(roomNum), blockNum(blockNum), count(0) {
    for (size_t index = 0; index < 3; ++index) {
        students[index] = nullptr;
    }
}

Obshtak::Obshtak(const Obshtak& other)
    : roomNum(other.roomNum), blockNum(other.blockNum), count(0) {
    for (size_t index = 0; index < 3; ++index) {
        students[index] = nullptr;
    }
}

Obshtak& Obshtak::operator=(const Obshtak& other) {
    if (this != &other) {
        clearResidents();
        roomNum = other.roomNum;
        blockNum = other.blockNum;
    }
    return *this;
}

Obshtak::~Obshtak() {
    clearResidents();
}

int Obshtak::getRoomNum() const {
    return roomNum;
}

int Obshtak::getBlockNum() const {
    return blockNum;
}

void Obshtak::setRoomNum(int newRoomNum) {
    roomNum = newRoomNum;
}

void Obshtak::setBlockNum(int newBlockNum) {
    blockNum = newBlockNum;
}

bool Obshtak::hasRoom() const {
    return count < 3;
}

void Obshtak::addStudent(Student& student) {
    if (!hasRoom()) {
        throw std::runtime_error("no room left");
    }

    if (student.obshtak == this) {
        return;
    }

    if (student.obshtak != nullptr) {
        throw std::runtime_error("student already lives in another dorm");
    }

    students[count++] = &student;
    student.setObshtak(this);
}

void Obshtak::evictStudentById(unsigned studentId) {
    for (size_t index = 0; index < count; ++index) {
        if (students[index]->id == studentId) {
            students[index]->setObshtak(nullptr);
            for (size_t shift = index + 1; shift < count; ++shift) {
                students[shift - 1] = students[shift];
            }
            students[count - 1] = nullptr;
            --count;
            return;
        }
    }

    throw std::runtime_error("student not found");
}

void Obshtak::printInfo() const {
    std::cout << "Obshtak room " << roomNum << ", block " << blockNum << '\n';
    if (count == 0) {
        std::cout << "No residents\n";
        return;
    }

    for (size_t index = 0; index < count; ++index) {
        std::cout << "Resident #" << (index + 1) << ": " << students[index]->getName()
                  << " (id " << students[index]->getId() << ")\n";
    }
}

void Obshtak::clearResidents() {
    for (size_t index = 0; index < count; ++index) {
        if (students[index] != nullptr) {
            students[index]->setObshtak(nullptr);
            students[index] = nullptr;
        }
    }
    count = 0;
}

int main() {
    try {
        Student s1("Ivan", 2004, 5.5f);
        Student s2("Maria", 2003, 5.9f);
        Student s3("Niki", 2002, 4.7f);

        Obshtak dorm(217, 3);
        dorm.addStudent(s1);
        dorm.addStudent(s2);
        dorm.addStudent(s3);

        dorm.printInfo();
        std::cout << "Has room: " << dorm.hasRoom() << '\n';

        s2.leaveObshtak();
        std::cout << "After Maria leaves:\n";
        dorm.printInfo();

        Obshtak copiedDorm = dorm;
        std::cout << "Copied dorm (must be empty):\n";
        copiedDorm.printInfo();
    } catch (const std::exception& ex) {
        std::cout << "Error: " << ex.what() << '\n';
    }

    return 0;
}
