#include <iostream>
#include <fstream>
#define MAX_ACHIEVEMENTS 10

enum Role{
    Mage, Warrior, Healer
};

struct Weapon{
    size_t damage; // 0-10
    float attack_speed;
};

struct Hero{
    char* name;
    size_t hp; // 0-100
    Role role;
    Weapon weapon;
};

void saveGameState(const Hero& hero, const bool* achievements, const size_t n, const size_t nameLen);
void loadGameState(Hero* hero, bool* achievements, size_t& n, size_t& nameLen);
bool checkAchievement(const int index);
void printInfo(const Hero hero, const bool* achievements, const size_t n);
size_t strlen_t(const char* str);

int main(){
    size_t n = 0, nameLen = 0;

    std::cout << "Enter N (Achievements):\n";
    // std::cin >> n;
    n = 5;

    Weapon ak47 = {6, 6.7};
    Role role = Mage;

    char* name = new (std::nothrow) char[10];
    if(!name){
        std::cout << "No malloc!\n";
        return 1;
    }

    std::cout << "Enter Name:\n";
    // std::cin >> name;
    strcpy(name, "asd");
    std::cout << "asd2 ";
    nameLen = strlen_t(name);

    Hero netanyahu = {name, 67, role, ak47};

    bool* achievements;
    achievements = new (std::nothrow) bool[n];
    if(!achievements){
        std::cout << "No malloc!\n";
        delete[] name;
        return 1;
    }

    if(n > 0) achievements[n - 1] = true;
    saveGameState(netanyahu, achievements, n, nameLen);
    printInfo(netanyahu, achievements, n);

    std::cout << "ACH: " << checkAchievement(n - 1) << std::endl;

    Hero* valio;
    bool* valioAch;

    loadGameState(valio, valioAch, n, nameLen);
    printInfo(*valio, valioAch, n);

    delete[] name;
    delete[] achievements;
    if(valio){
        delete[] valio->name;
        delete valio;
    }
    delete[] valioAch;

    return 0;
}

void saveGameState(const Hero& hero, const bool* achievements, const size_t n, const size_t nameLen){
    std::ofstream oFile("save.dat", std::ios::out | std::ios::binary);
    if(!oFile.good()){
        std::cout << "No file.." << std::endl;
        return;
    }

    // ------
    oFile.write((const char*) &n, sizeof(n)); // achievements
    oFile.write((const char*) &nameLen, sizeof(nameLen)); // strlen(name);
    // ------

    oFile.write((const char*) hero.name, nameLen);
    oFile.write((const char*) hero.hp, sizeof(hero.hp));
    oFile.write((const char*) hero.role, sizeof(hero.role));
    oFile.write((const char*) &hero.weapon, sizeof(hero.weapon));

    oFile.write((const char*) achievements, n * sizeof(bool));

    oFile.close();
}

void loadGameState(Hero* hero, bool* achievements, size_t& n, size_t& nameLen){
    std::ifstream iFile("save.dat", std::ios::in | std::ios::binary);
    if(!iFile.good()){
        std::cout << "No file.." << std::endl;
        return;
    }   

    iFile.read((char*) n, sizeof(n)); // achievements
    iFile.read((char*) nameLen, sizeof(nameLen)); // strlen(name);

    if(!n || !nameLen || n < 0 || nameLen < 0) return;

    hero = new (std::nothrow) Hero;
    hero->name = new (std::nothrow) char[nameLen + 1];
    achievements = new (std::nothrow) bool[n];

    if(!hero || !hero->name || !achievements) {
        delete[] hero->name;
        delete[] achievements;
        delete hero;
        return;
    }

    iFile.read((char*) hero->name, nameLen);
    iFile.read((char*) hero->hp, sizeof(hero->hp));
    iFile.read((char*) hero->role, sizeof(hero->role));
    iFile.read((char*) &hero->weapon, sizeof(hero->weapon));
    iFile.read((char*) achievements, n * sizeof(bool));

    iFile.close();
}

void printInfo(const Hero hero, const bool* achievements, const size_t n){
    std::cout << "Hero: " << hero.name << "\nHP [" << hero.hp << "]" << std::endl;
    std::cout << "Role: " << hero.role;

    std::cout << "\n\nCompleted Achievements:\n";
    for(int i = 0; i < n; i++){
        if(achievements[i]) 
            std::cout << "[" << i << "]";
    }
    
    std::cout << std::endl;
}

bool checkAchievement(const int index){
    std::ifstream iFile("save.dat", std::ios::in | std::ios::binary);
    if(!iFile.good()){
        std::cout << "No file.." << std::endl;
        return false;
    }

    iFile.seekg(sizeof(Hero) + index * sizeof(bool));
    bool isComplete;
    iFile.read((char*) &isComplete, sizeof(bool));

    return isComplete;
}

size_t strlen_t(const char* str){
    size_t size = 0;
    for(;str[size] != '\0' && str[size] != '\n'; size++);
    return size;
}