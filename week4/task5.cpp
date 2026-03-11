#include <iostream>
#include <fstream>
#define MAX_ACHIEVEMENTS 10

enum Class{
    Mage, Warrior, Healer
};

struct Weapon{
    size_t damage; // 0-10
    float attack_speed;
};

struct Hero{
    char name[10]; // ;)
    size_t hp; // 0-100
    Class role;
    Weapon weapon;
};

void saveGameState(Hero hero, bool* achievements){
    std::ofstream oFile("save.dat", std::ios::out | std::ios::binary);
    if(!oFile.good()){
        std::cout << "No file.." << std::endl;
        return;
    }
    
    oFile.write((const char*) &hero, sizeof(Hero));
    oFile.write((const char*) achievements, MAX_ACHIEVEMENTS * sizeof(bool));

    oFile.close();
}

void loadGameState(Hero& hero, bool* achievements){
    std::ifstream iFile("save.dat", std::ios::in | std::ios::binary);
    if(!iFile.good()){
        std::cout << "No file.." << std::endl;
        return;
    }   

    iFile.read((char*) &hero, sizeof(Hero));
    iFile.read((char*) achievements, MAX_ACHIEVEMENTS * sizeof(bool));

    iFile.close();
}

bool checkAchievement(int index){
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

void printInfo(Hero hero, bool* achievements){
    std::cout << "Hero: " << hero.name << "\nHP [" << hero.hp << "]" << std::endl;
    std::cout << "Role: " << hero.role; // murzi me da pravq da se printira stringa i weapon

    std::cout << "\n\nCompleted Achievements:\n";
    for(int i = 0; i < MAX_ACHIEVEMENTS; i++){
        if(achievements[i]) 
            std::cout << "[" << i << "]";
    }
    
    std::cout << std::endl;
}

int main(){
    Weapon ak47 = {6, 6.7};
    Class role = Mage;

    // char* name = new (std::nothrow) char[10];
    // if(!name){
    //     std::cout << "No malloc!\n";
    //     return 1;
    // }
    // strcpy(name, "Ben");

    Hero netanyahu = {"Ben", 67, role, ak47};
    // Hero* netanyahu = new (std::nothrow) Hero;
    // if(!netanyahu){
    //     std::cout << "No malloc!\n";
    //     return 1;
    // }
    // netanyahu->name = new (std::nothrow) char[10];
    // if(!netanyahu->name){
    //     std::cout << "No malloc!\n";
    //     return 1;
    // }

    bool* achievements;
    achievements = new (std::nothrow) bool[MAX_ACHIEVEMENTS];
    if(!achievements){
        std::cout << "No malloc!\n";
        return 1;
    }
    achievements[6] = true;
    achievements[7] = true;
    
    saveGameState(netanyahu, achievements);
    printInfo(netanyahu, achievements);
    std::cout << "ACH: " << checkAchievement(6) << std::endl;
    std::cout << "ACH: " << checkAchievement(8) << std::endl;

    Hero vailo;
    bool* valioAch;
    valioAch = new (std::nothrow) bool[MAX_ACHIEVEMENTS];
    if(!valioAch){
        std::cout << "No malloc!\n";
        return 1;
    }
    // vailo.name = new (std::nothrow) char[10];
    // if(!vailo.name){
    //     std::cout << "No malloc!\n";
    //     return 1;
    // }
    loadGameState(vailo, valioAch);
    printInfo(vailo, valioAch);

    return 0;
}