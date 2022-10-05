
#ifndef ASSIGNMENT_1_BIGDECIMALINT_H
#define ASSIGNMENT_1_BIGDECIMALINT_H

#include <iostream>
#include<deque>

using namespace std;

class BigDecimalInt {
public:
    friend ostream& operator<<(ostream& out,const BigDecimalInt& bigint);
public:
    BigDecimalInt(const string& num);
    BigDecimalInt(const int& num=0);
    BigDecimalInt(const BigDecimalInt& num);

    int getSize()const;
    char getSign()const;

    BigDecimalInt& operator=(const BigDecimalInt& num);
    BigDecimalInt operator+(const BigDecimalInt& num);
    BigDecimalInt operator-(const BigDecimalInt& num);


private:
    deque<char> digits;
    char sign;
    void setSign(char sign);
};


#endif //ASSIGNMENT_1_BIGDECIMALINT_H
