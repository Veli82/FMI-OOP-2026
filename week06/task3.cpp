#include "../lib/ezlib.h"
#include <iostream>
#include <ios>
#include <fstream>
#include <stdexcept>

class Game{
    public:
        Game(){
            strcpy_t(mTitle, (u8*) "Ben 10");
            mPrice = 6.7;
            mIsAvailable = true;
        }
        void print(){
            std::cout << "-- Game -- " << std::endl;
            std::cout << "Title: " << mTitle << std::endl;
            std::cout << "Price: " << mPrice << std::endl;
            std::cout << "Available: " << mIsAvailable << std::endl;
        }
        bool isFree(){
            return mPrice == 0.0;
        }
    
        void setTitle(const u8 *title) {
            if(!title) throw std::invalid_argument("Title can't be empty");
            if(strlen_t(title) >= 64) throw std::invalid_argument("Title len (1-64)");
            strcpy_t(mTitle, title);
        }
        void setPrice(const f32 price) {mPrice = price;} 
        void setIsAvailable(bool isAvailable) {mIsAvailable = isAvailable;}

        const u8* getTitle() const {return mTitle;}
        f32 getPrice() const {return mPrice;} 
        bool getIsAvailable() const {return mIsAvailable;}
    private:
        f32 mPrice;
        u8 mTitle[64];
        bool mIsAvailable;
};

class GamePlatform{ // as vector
    public:
        GamePlatform(){
            mGames = new Game[1];
            mCapacity = 1;
            mCurrent = 0;
        }

        i32 getCount() const {
            return mCurrent;
        }

        void addGame(const Game game){
            if (mCurrent == mCapacity){
                Game* temp = new Game[2 * mCapacity];

                for (i32 i = 0; i < mCapacity; i++) 
                    temp[i] = mGames[i];

                delete[] mGames;
                mCapacity *= 2;
                mGames = temp;
            }
            mGames[mCurrent++] = game;
        }

        Game getGameAt(const i32 index){
            if (index >= 0 && index < mCurrent) return mGames[index];
            throw std::out_of_range("Index out of range");
        }
        const Game* getAllGames() const {
            return mGames;
        }
        Game getCheapestGame() const {
            if(!mGames) throw std::out_of_range("No games");
            u32 cheapestIndex = 0;
            for(i32 i = 0; i < mCurrent; i++){
                if(mGames[i].getPrice() < mGames[cheapestIndex].getPrice())
                    cheapestIndex = i;
            }
            return mGames[cheapestIndex];
        }
        Game getExpensivestGame() const {
            if(!mGames) throw std::out_of_range("No games");
            u32 expensiveIndex = 0;
            for(i32 i = 0; i < mCurrent; i++){
                if(mGames[i].getPrice() > mGames[expensiveIndex].getPrice())
                    expensiveIndex = i;
            }
            return mGames[expensiveIndex];
        }
        void printAllFreeGames(){
            for(i32 i = 0; i < mCurrent; i++){
                if(mGames[i].isFree()) mGames[i].print();
            }
        }
        void removeGame(const Game game) {
            for(i32 i = 0; i < mCurrent; i++){
                if(mGames[i].getTitle() == game.getTitle()){ // no overloading :(
                    for(i32 j = i; j < mCurrent - 1; j++)
                        mGames[j] = mGames[j + 1];
                    mCurrent--;
                    return;
                }
            }
            throw std::invalid_argument("No such game");
        }
        void saveGame(const char* fileName, bool isBinary){
            if(!fileName) throw std::invalid_argument("Invalid filename");
            if(!isBinary) throw std::invalid_argument("Only binary mode is supported"); // :)

            std::ofstream file(fileName, std::ios::binary);
            if(!file) throw std::runtime_error("Failed to open file");

            file.write((const char*)&mCurrent, sizeof(mCurrent));
           

            for(i32 i = 0; i < mCurrent; i++){
                f32 price = mGames[i].getPrice();
                bool isAvailable = mGames[i].getIsAvailable(); 

                file.write((const char*)mGames[i].getTitle(), 64);
                file.write((const char*)&price, sizeof(price));
                file.write((const char*)&isAvailable, sizeof(isAvailable));
            }
        }

        void loadGame(const char* fileName, bool isBinary){
            if(!fileName) throw std::invalid_argument("Invalid filename");
            if(!isBinary) throw std::invalid_argument("Only binary mode is supported"); // :) ne moga trqbva da ocenish hustle-a da gi napravq ne moga da si igraq s textovi failove bratttt..

            std::ifstream file(fileName, std::ios::binary);
            if(!file) throw std::runtime_error("Failed to open file");

            i32 count = 0;
            file.read((char*)&count, sizeof(count));
            if(!file || count < 0) throw std::runtime_error("Corrupted binary file");

            resetStorage(count == 0 ? 1 : count);

            u8 title[64] = {0};
            f32 price = 0;
            bool isAvailable = false;

            for(i32 i = 0; i < count; i++){
                file.read((char*)title, 64);
                file.read((char*)&price, sizeof(price));
                file.read((char*)&isAvailable, sizeof(isAvailable));
                if(!file) throw std::runtime_error("Corrupted binary file");

                Game game;
                game.setTitle(title);
                game.setPrice(price);
                game.setIsAvailable(isAvailable);
                addGame(game);
            }
        }

        ~GamePlatform() { delete[] mGames; }
    private:
        // capacity of the vector
        i32 mCapacity;
        // current is the number of elements
        i32 mCurrent;
        // games is the array
        Game *mGames;
        
        void resetStorage(i32 newCapacity){
            delete[] mGames;
            mCapacity = newCapacity;
            mCurrent = 0;
            mGames = new Game[mCapacity];
        }
};

int main(){
    Game g1;
    g1.setTitle((u8*)"Doom");
    g1.setPrice(19.99);
    g1.setIsAvailable(true);

    Game g2;
    g2.setTitle((u8*)"Portal 2");
    g2.setPrice(0.0);
    g2.setIsAvailable(true);

    GamePlatform platform;
    platform.addGame(g1);
    platform.addGame(g2);

    platform.saveGame("games.bin", true);

    GamePlatform fromBinary;
    fromBinary.loadGame("games.bin", true);
    std::cout << "Loaded from binary: " << fromBinary.getCount() << std::endl;
    fromBinary.getGameAt(1).print();

    return 0;
}
