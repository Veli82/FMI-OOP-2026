#include <../lib/ezlib.h>
#include <iostream>
// #define MAX_GAMES 32

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
            return mPrice == 0.0 ? true : false;
        }
    
        void setTitle(u8 *title) {
            if(!title) return;
            if(strlen_t(title) >= 64) return;
            strcpy_t(mTitle, title);
        }
        void setPrice(f32 price) {mPrice = price;} 
        void setIsAvailable(bool isAvailable) {mIsAvailable = isAvailable;}

        const u8* getTitle() const {return mTitle;}
        const f32 getPrice() const {return mPrice;} 
        const bool getIsAvailable() const {return mIsAvailable;}
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

        void addGame(Game game){
            if (mCurrent == mCapacity){
                Game* temp = new Game[2 * mCapacity];

                for (int i = 0; i < mCapacity; i++) 
                    temp[i] = mGames[i];

                delete[] mGames;
                mCapacity *= 2;
                mGames = temp;
            }
            mGames[mCurrent++] = game;
        }

        Game* getGameAt(i32 index){
            if (index < mCurrent)
                return (mGames + index);
            return nullptr;
        }
        
        


        ~GamePlatform() { delete[] mGames; }
    private:
        // capacity is the total storage
        // capacity of the platform
        i32 mCapacity;
        // current is the number of elements
        // currently present in the platform
        i32 mCurrent;

        // games is the array
        Game *mGames;
};

int main(){

    return 0;
}