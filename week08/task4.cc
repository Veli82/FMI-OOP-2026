#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <utility>

char* duplicateText(const char* text) {
    if (!text) {
        throw std::invalid_argument("null text");
    }

    size_t length = std::strlen(text);
    char* copy = new char[length + 1];
    std::strcpy(copy, text);
    return copy;
}

void writeString(std::ostream& out, const char* text) {
    size_t length = std::strlen(text);
    out.write((const char*)(&length), sizeof(length));
    out.write(text, (std::streamsize)(length));
}

char* readString(std::istream& in) {
    size_t length = 0;
    in.read((char*)(&length), sizeof(length));
    if (!in) {
        throw std::runtime_error("failed to read string length");
    }

    char* text = new char[length + 1];
    in.read(text, (std::streamsize)(length));
    if (!in) {
        delete[] text;
        throw std::runtime_error("failed to read string data");
    }

    text[length] = '\0';
    return text;
}

class Beverage {
public:
    Beverage()
        : name(nullptr), alcoholic(false) {
        setName("Water");
    }

    Beverage(const char* name, bool alcoholic)
        : name(nullptr), alcoholic(alcoholic) {
        setName(name);
    }

    Beverage(const Beverage& other)
        : name(nullptr), alcoholic(other.alcoholic) {
        setName(other.name);
    }

    Beverage& operator=(Beverage other) {
        swap(other);
        return *this;
    }

    ~Beverage() {
        delete[] name;
    }

    const char* getName() const {
        return name;
    }

    bool isAlcoholic() const {
        return alcoholic;
    }

    void setName(const char* newName) {
        char* copy = duplicateText(newName);
        delete[] name;
        name = copy;
    }

    void setAlcoholic(bool newAlcoholic) {
        alcoholic = newAlcoholic;
    }

    void printInfo() const {
        std::cout << name << " | " << (alcoholic ? "alcoholic" : "non-alcoholic") << '\n';
    }

    void saveToBinary(std::ostream& out) const {
        writeString(out, name);
        out.write((const char*)(&alcoholic), sizeof(alcoholic));
    }

    void loadFromBinary(std::istream& in) {
        char* loadedName = readString(in);
        bool loadedAlcoholic = false;
        in.read((char*)(&loadedAlcoholic), sizeof(loadedAlcoholic));
        if (!in) {
            delete[] loadedName;
            throw std::runtime_error("failed to read beverage alcohol flag");
        }

        delete[] name;
        name = loadedName;
        alcoholic = loadedAlcoholic;
    }

    void swap(Beverage& other) noexcept {
        std::swap(name, other.name);
        std::swap(alcoholic, other.alcoholic);
    }

private:
    char* name;
    bool alcoholic;
};

class Coctail {
public:
    Coctail()
        : name(nullptr), count(0) {
        setName("Unnamed");
    }

    Coctail(const char* name)
        : name(nullptr), count(0) {
        setName(name);
    }

    Coctail(const Coctail& other)
        : name(nullptr), count(other.count) {
        setName(other.name);
        for (size_t index = 0; index < count; ++index) {
            beverages[index] = other.beverages[index];
        }
    }

    Coctail& operator=(Coctail other) {
        swap(other);
        return *this;
    }

    ~Coctail() {
        delete[] name;
    }

    const char* getName() const {
        return name;
    }

    size_t getCount() const {
        return count;
    }

    void setName(const char* newName) {
        char* copy = duplicateText(newName);
        delete[] name;
        name = copy;
    }

    void addBeverage(const Beverage& beverage) {
        if (count == 6) {
            throw std::runtime_error("cocktail is full");
        }

        beverages[count++] = beverage;
    }

    bool hasAlcohol() const {
        for (size_t index = 0; index < count; ++index) {
            if (beverages[index].isAlcoholic()) {
                return true;
            }
        }
        return false;
    }

    void printInfo() const {
        std::cout << "Coctail: " << name << '\n';
        for (size_t index = 0; index < count; ++index) {
            std::cout << "  ";
            beverages[index].printInfo();
        }
    }

    void saveToBinary(std::ostream& out) const {
        writeString(out, name);
        out.write((const char*)(&count), sizeof(count));
        for (size_t index = 0; index < count; ++index) {
            beverages[index].saveToBinary(out);
        }
    }

    void loadFromBinary(std::istream& in) {
        char* loadedName = readString(in);
        size_t loadedCount = 0;
        in.read((char*)(&loadedCount), sizeof(loadedCount));
        if (!in) {
            delete[] loadedName;
            throw std::runtime_error("failed to read cocktail count");
        }

        if (loadedCount > 6) {
            delete[] loadedName;
            throw std::runtime_error("too many beverages");
        }

        Coctail loaded(loadedName);
        delete[] loadedName;

        for (size_t index = 0; index < loadedCount; ++index) {
            Beverage beverage;
            beverage.loadFromBinary(in);
            loaded.addBeverage(beverage);
        }

        swap(loaded);
    }

    void saveToBinaryFile(const char* fileName) const {
        std::ofstream out(fileName, std::ios::binary);
        if (!out) {
            throw std::runtime_error("failed to open binary file");
        }

        saveToBinary(out);
    }

    void loadFromBinaryFile(const char* fileName) {
        std::ifstream in(fileName, std::ios::binary);
        if (!in) {
            throw std::runtime_error("failed to open binary file");
        }

        Coctail loaded;
        loaded.loadFromBinary(in);
        swap(loaded);
    }

    void swap(Coctail& other) noexcept {
        std::swap(name, other.name);
        std::swap(count, other.count);
        for (size_t index = 0; index < 6; ++index) {
            beverages[index].swap(other.beverages[index]);
        }
    }

private:
    char* name;
    Beverage beverages[6];
    size_t count;
};

int main() {
    try {
        Beverage gin("Gin", true);
        Beverage tonic("Tonic", false);
        Beverage lime("Lime juice", false);

        Coctail c1("Gin Tonic");
        c1.addBeverage(gin);
        c1.addBeverage(tonic);
        c1.addBeverage(lime);

        c1.printInfo();
        std::cout << "Has alcohol: " << c1.hasAlcohol() << '\n';

        c1.saveToBinaryFile("task4_cocktail.bin");

        Coctail fromText;
        std::cout << "Loaded from text:\n";
        fromText.printInfo();

        Coctail fromBinary;
        fromBinary.loadFromBinaryFile("task4_cocktail.bin");
        std::cout << "Loaded from binary:\n";
        fromBinary.printInfo();
    } catch (const std::exception& ex) {
        std::cout << "Error: " << ex.what() << '\n';
    }

    return 0;
}
