#include <iostream>

class BankAccount{
    public:
        BankAccount(double balance) : mbalance(balance) {
        }
        BankAccount operator+(BankAccount& other){
            BankAccount temp(mbalance + other.mbalance);
            
            this->mbalance = 0;
            other.mbalance = 0;

            return temp;
        }
        BankAccount operator==(const BankAccount& other){
            return this == &other;
        }
        bool deposit(double amount){
            return mbalance += amount;
        }   
        bool withdraw(double amount){
            if(mbalance < amount) return false;
            return mbalance -= amount;
        }   
        double getBalance() const {
            return this->mbalance;
        }
        size_t getAccNumber() const {
            return this->maccNumber;
        }
        void setBalance(double balance) {
            this->mbalance = balance;
        }
    private:
        double mbalance = 0;
        static size_t maccNumber;
};

size_t BankAccount::maccNumber = 67;
std::ostream& operator<<(std::ostream& o, const BankAccount& bank){
    o << "ACC: " << bank.getAccNumber() << std::endl; 
    o << "Money: " << bank.getBalance() << std::endl;
    return o;
}

class SavingsAccount : public BankAccount{
    public:
        SavingsAccount() : BankAccount(100) {
            
        }
    private:
};


int main(){
    SavingsAccount sav;
    sav.withdraw(10);


    return 0;
}

