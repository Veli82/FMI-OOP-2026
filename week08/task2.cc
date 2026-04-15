#include <iostream>
#include <fstream>
#include <limits>
#include <stdexcept>
#include <string>
#include "../lib/ezlib.h"

char* cloneString(const char* text) {
    if (!text) throw std::invalid_argument("null string");

    char* copy = new char[strlen_t(text) + 1];
    strcpy_t(copy, text);
    return copy;
}

void writeBinaryString(std::ostream& out, const char* text) {
    size_t length = strlen_t(text);
    out.write((const char*)(&length), sizeof(length));
    out.write(text, length);
}

char* readBinaryString(std::istream& in) {
    size_t length = 0;
    in.read((char*)(&length), sizeof(length));
    if (!in) {
        throw std::runtime_error("failed to read string length");
    }

    char* text = new char[length + 1];
    in.read(text, length);
    if (!in) {
        delete[] text;
        throw std::runtime_error("failed to read string data");
    }

    text[length] = '\0';
    return text;
}

class CPU {
    public:
        CPU() : model(nullptr), clockSpeed(0) {
            setClockSpeed(5);
            setModel("Cryplex");
        }

        CPU(const CPU& other) : model(nullptr), clockSpeed(other.clockSpeed) {
            setModel(other.model);
        }

        CPU& operator=(CPU other) {
            swap(other);
            return *this;
        }

        ~CPU() {
            delete[] model;
        }

        size_t getClockSpeed() const { return clockSpeed; }
        const char *getModel() const { return model; }

        void setClockSpeed(size_t clockSpeed) { this->clockSpeed = clockSpeed; }

        void setModel(const char *model) {
            char* newModel = cloneString(model);
            delete[] this->model;
            this->model = newModel;
        }

        void saveToBinary(std::ostream& out) const {
            writeBinaryString(out, model);
            out.write((const char*)(&clockSpeed), sizeof(clockSpeed));
        }

        void loadFromBinary(std::istream& in) {
            char* newModel = readBinaryString(in);
            size_t newClockSpeed = 0;
            in.read((char*)(&newClockSpeed), sizeof(newClockSpeed));
            if (!in) {
                delete[] newModel;
                throw std::runtime_error("failed to read CPU clock speed");
            }

            delete[] model;
            model = newModel;
            clockSpeed = newClockSpeed;
        }

        void swap(CPU& other) {
            std::swap(model, other.model);
            std::swap(clockSpeed, other.clockSpeed);
        }

    private:
        char *model;
        size_t clockSpeed;
};

class Display {
    public:
        Display() : refreshRate(0), width(0), height(0) {
            setRefreshRate(240);
            setWidth(1920);
            setHeight(1080);
        }

        Display(const Display& other) = default;
        Display& operator=(const Display& other) = default;
        ~Display() = default;

        size_t getRefreshRate() const { return refreshRate; }
        size_t getWidth() const { return width; }
        size_t getHeight() const { return height; }

        void setRefreshRate(size_t refreshRate) { this->refreshRate = refreshRate; }
        void setWidth(size_t width) { this->width = width; }
        void setHeight(size_t height) { this->height = height; }

        void saveToBinary(std::ostream& out) const {
            out.write((const char*)(&refreshRate), sizeof(refreshRate));
            out.write((const char*)(&width), sizeof(width));
            out.write((const char*)(&height), sizeof(height));
        }

        void loadFromBinary(std::istream& in) {
            size_t newRefreshRate = 0;
            size_t newWidth = 0;
            size_t newHeight = 0;

            in.read((char*)(&newRefreshRate), sizeof(newRefreshRate));
            in.read((char*)(&newWidth), sizeof(newWidth));
            in.read((char*)(&newHeight), sizeof(newHeight));

            if (!in) {
                throw std::runtime_error("failed to read display data");
            }

            setRefreshRate(newRefreshRate);
            setWidth(newWidth);
            setHeight(newHeight);
        }

    private:
        size_t refreshRate;
        size_t width;
        size_t height;
};

class Laptop {
    public:
        Laptop() : ryzenCpu(), display(), brand(nullptr) {
            setBrand("Racerist");
        }

        Laptop(const Laptop& other)
            : ryzenCpu(other.ryzenCpu), display(other.display), brand(nullptr) {
            setBrand(other.brand);
        }

        Laptop& operator=(Laptop other) {
            swap(other);
            return *this;
        }

        ~Laptop() {
            delete[] brand;
        }

        CPU getCpu() const { return ryzenCpu; }
        Display getDisplay() const { return display; }
        const char *getBrand() const { return brand; }

        void setCpu(const CPU& cpu) { this->ryzenCpu = cpu; }
        void setDisplay(const Display& display) { this->display = display; }

        void setBrand(const char *brand) {
            char* newBrand = cloneString(brand);
            delete[] this->brand;
            this->brand = newBrand;
        }

        void saveToBinary(std::ostream& out) const {
            writeBinaryString(out, brand);
            ryzenCpu.saveToBinary(out);
            display.saveToBinary(out);
        }

        void loadFromBinary(std::istream& in) {
            char* newBrand = readBinaryString(in);

            CPU newCpu;
            Display newDisplay;

            try {
                newCpu.loadFromBinary(in);
                newDisplay.loadFromBinary(in);
            } catch (...) {
                delete[] newBrand;
                throw;
            }

            delete[] brand;
            brand = newBrand;
            ryzenCpu = newCpu;
            display = newDisplay;
        }

        void saveToBinaryFile(const char* fileName) const {
            std::ofstream out(fileName, std::ios::binary);
            if (!out) throw std::runtime_error("failed to open binary file for writing");
            saveToBinary(out);
        }

        void loadFromBinaryFile(const char* fileName) {
            std::ifstream in(fileName, std::ios::binary);
            if (!in) throw std::runtime_error("failed to open binary file for reading");
            Laptop loaded;

            loaded.loadFromBinary(in);
            swap(loaded);
        }

        void swap(Laptop& other) {
            ryzenCpu.swap(other.ryzenCpu);
            std::swap(display, other.display);
            std::swap(brand, other.brand);
        }

    private:
        CPU ryzenCpu;
        Display display;
        char *brand;
};

int main(void){
    try {
        Laptop first;
        first.setBrand("Lenono");

        CPU cpu;
        cpu.setModel("Ryzen 9 9950X3D");
        cpu.setClockSpeed(57);
        first.setCpu(cpu);

        Display display;
        display.setRefreshRate(165);
        display.setWidth(2560);
        display.setHeight(1440);
        first.setDisplay(display);

        first.saveToBinaryFile("task2_laptop.bin");

        Laptop loaded;
        loaded.loadFromBinaryFile("task2_laptop.bin");

        std::cout << "Loaded brand: " << loaded.getBrand() << '\n';
        std::cout << "Loaded cpu model: " << loaded.getCpu().getModel() << '\n';
        std::cout << "Loaded cpu clock: " << loaded.getCpu().getClockSpeed() << '\n';
        std::cout << "Loaded display: "
                  << loaded.getDisplay().getWidth() << 'x' << loaded.getDisplay().getHeight()
                  << " @" << loaded.getDisplay().getRefreshRate() << "Hz\n";
    } catch (const std::exception& ex) {
        std::cout << "Error: " << ex.what() << '\n';
    }

    return 0;
}