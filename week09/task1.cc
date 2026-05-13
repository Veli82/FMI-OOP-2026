#include <iostream>

class ComplexNum {
    public:
        ComplexNum() {
        }
        ComplexNum(float R, float C) {
            setR(R);
            setC(C);
        }

        ComplexNum(const ComplexNum& other) {
            this->R = other.getR();
            this->C = other.getC();
        }

        ComplexNum& operator=(const ComplexNum& other) {
            if (this != &other) {
                this->R = other.getR();
                this->C = other.getC();
            }
            return *this;
        }

        ComplexNum& operator+=(const ComplexNum& other){
            this->R += other.getR();
            this->C += other.getC();
            
            return *this;
        }

        ComplexNum operator+(const ComplexNum& other){
            ComplexNum ret(*this);
            ret += other;
            return ret;
        }

        ComplexNum& operator-=(const ComplexNum& other){
            this->R -= other.getR();
            this->C -= other.getC();
            
            return *this;
        }

        ComplexNum operator-(const ComplexNum& other){
            ComplexNum ret(*this);
            
            ret -= other;
            
            return ret;
        }

        ComplexNum& operator*=(const ComplexNum& other){
            // (a + bi) * (c + di) == (ac - bd) + i(ad + cb)
            this->R = this->R * other.getR();
            this->R -= this->C * other.getC();

            this->C = this->R * other.getC();
            this->C += this->C * other.getR();

            return *this;
        }

        ComplexNum operator*(const ComplexNum& other){
            ComplexNum ret(*this);
            
            ret *= other;

            return ret;
        }

        // ComplexNum operator/=(const ComplexNum& other){
        //     return *this;
        // } tva nq go pisha

        // ComplexNum& operator/(const ComplexNum& other){
        //     ComplexNum ret(*this);
        //     return ret;
        // }

        bool operator==(const ComplexNum& b){
            return this->C == b.getC() && this->R == b.getR();
        }
        bool operator!=(const ComplexNum& b){
            return this->C != b.getC() || this->R != b.getR();
        }

        // float operator()(){ i wont do ts bro

        // }

        friend std::ostream& operator<<(std::ostream& o, const ComplexNum& c){
            o << "NUM: ";
            o << c.getR();
            o << " ";
            o << c.getC();
            o << "\n";

            return o;
        }
        
        friend std::istream& operator>>(std::istream& i, ComplexNum& c){
        

            return o;
        }

        ~ComplexNum() {
            this->R = 0.0;
            this->C = 0.0;
        }

        void setR(float R){
            this->R = R;
        }
        void setC(float C){
            this->C = C;
        }

        float getR() const {
            return this->R;
        }

        float getC() const {
            return this->C;  
        }

    private:
        float R;
        float C;
};




int main(void){
    ComplexNum A(5.0, 10.0);

    std::cout << A;

    return 0;
}