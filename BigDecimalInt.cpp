#include <bits/stdc++.h>
#include <regex>
#include "BigDecimalInt.h"
using namespace std;


// ******************************** String Constructor ****************************


BigDecimalInt::BigDecimalInt(const string& num) {
    bool valid= true;
    bool leadingZero = true;
    if (! regex_match(num, regex("(\\+|-)?\\d+") ) )
        valid = false;
    else {
        if(isdigit(num[0]) && num[0] != '0') {
            digits.push_back(num[0]);
            leadingZero = false;
        }
        for (int i = 1; i <num.size() ; ++i) {
            if(num[i] == '0' && leadingZero)
                continue;
            leadingZero = false;
            digits.push_back(num[i]);
        }
    }
    if(!valid || leadingZero)
    {
        digits.push_back('0');
        setSign('+');
    }
    else{
        setSign(num[0]);
    }
}


// ******************************** Int Constructor ****************************


BigDecimalInt::BigDecimalInt(const int & num) {
    int temp=num;
    if(num==0)
    {
        digits.push_back('0');
        setSign('+');
    }
    else if(num<0)
    {
        setSign('-');
        temp*=-1;

    }
    else
    {
        setSign('+');
    }
    while(temp)
    {
        int digit=num%10;
        temp/=10;
        digits.push_front(digit + '0');
    }
}


// ******************************* Size Getter Function *****************************


int BigDecimalInt::getSize() const {
    return  digits.size();
}


// ******************************* Sign Getter Function *****************************


char BigDecimalInt::getSign() const {
    return  sign;
}

// ******************************** Sign Setter Function ****************************


void BigDecimalInt::setSign(const char& sign) {
    if(!isdigit(sign))
    {
        this->sign = sign;
    }
    else
    {
        this->sign = '+';
    }
}


// ***************************** Constructor Assign to Another Class Member *******************************


BigDecimalInt::BigDecimalInt(const BigDecimalInt &other) {
    *this = other;
}


// ******************************* Assign Operator Function *****************************


BigDecimalInt& BigDecimalInt::operator=(const BigDecimalInt &num) {
    this->digits.clear();
    for (int i = 0; i <num.getSize(); ++i) {
        digits.push_back(num.digits[i]);
    }
    return *this;
}


// ******************************** Addition Function ****************************


BigDecimalInt BigDecimalInt::operator+(const BigDecimalInt &num)const {
    if(this->getSign() != num.getSign())
    {
        //return *this-num;
        cout<<"MINUS\n";
    }
    int carry = 0 ;
    int leftIdx = this->getSize() - 1;
    int rightIdx = num.getSize() - 1;

    BigDecimalInt result;
    result.digits.clear();
    while (leftIdx >= 0 && rightIdx >= 0)
    {
        int d1 =  this->digits[leftIdx] - '0';
        int d2 =  num.digits[rightIdx] - '0';
        int sum = d1+d2+carry;
        if(sum>9)
        {
            carry = 1;
            sum%=10;
        }
        else
        {
            carry = 0;
        }
        result.digits.push_front(sum + '0');
        leftIdx--;
        rightIdx--;
    }
    while (leftIdx >= 0)
    {
        int d1 = this->digits[leftIdx] - '0';
        int sum = d1+carry;
        if(sum>9)
        {
            carry = 1;
            sum%=10;
        }
        else
        {
            carry = 0;
        }
        result.digits.push_front(sum + '0');
        leftIdx--;
    }
    while (rightIdx >=0)
    {
        int d1 = num.digits[rightIdx] - '0';
        int sum = d1+carry;
        if(sum>9)
        {
            carry = 1;
            sum%=10;
        }
        else
        {
            carry = 0;
        }
        result.digits.push_front(sum + '0');
        rightIdx--;
    }
    if(carry)
    {
        result.digits.push_front(carry + '0');
    }
    result.setSign(this->getSign());
    return  result;
}


// ****************************** Output Operator Overloading Function ******************************


ostream& operator<<(ostream& out,const BigDecimalInt& bigint) {
    if(bigint.getSign()=='-')
        out<<'-';

    for (int i = 0; i <bigint.getSize(); ++i) {
        out<<bigint.digits[i];
    }
    return out;
}


// ******************************* Less Than Check Function *****************************


bool BigDecimalInt::operator< (const BigDecimalInt& anotherDec)const{
    if(this->getSign()=='-'&&anotherDec.getSign()=='+')
        return true;

    if(this->getSign()=='+'&&anotherDec.getSign()=='-')
        return false;

    if(this->getSign()=='-' && anotherDec.getSign()=='-')
    {
        BigDecimalInt LHS = *this;
        LHS.setSign('+');
        BigDecimalInt RHS = anotherDec;
        RHS.setSign('+');
        return (LHS>RHS);
    }

    if(this->getSize() < anotherDec.getSize()){
        return true;
    }
    if(this->getSize() > anotherDec.getSize()){
        return false;
    }
    for(long long i = 0; i < anotherDec.getSize(); i++){
        if(anotherDec.digits[i] > this->digits[i])
            return true;
        else if(anotherDec.digits[i] < this->digits[i])
            return false;
    }
    return false;
}


// ****************************** Greater Than Check Function ******************************


bool BigDecimalInt::operator> (const BigDecimalInt& anotherDec)const{
    if(this->getSign()=='-' && anotherDec.getSign()=='+')
        return false;

    if(this->getSign()=='+' && anotherDec.getSign()=='-')
        return true;

    if(this->getSign()=='-' && anotherDec.getSign()=='-')
    {
        BigDecimalInt LHS = *this;
        LHS.setSign('+');
        BigDecimalInt RHS = anotherDec;
        RHS.setSign('+');
        return (LHS<RHS);
    }

    if(this->getSize() < anotherDec.getSize()){
        return false;
    }
    if(this->getSize() > anotherDec.getSize()){
        return true;
    }
    for(long long i = 0; i < anotherDec.getSize(); i++){
        if(anotherDec.digits[i] > this->digits[i])
            return false;
        else if(anotherDec.digits[i] < this->digits[i])
            return true;
    }
    return false;
}


// ****************************** Equality Check Functions******************************


bool BigDecimalInt::operator==(const BigDecimalInt& anotherDec) const {
    return (!(*this < anotherDec) && !(*this > anotherDec));
}


// ***************************** Subtraction Function *******************************


BigDecimalInt BigDecimalInt::operator-(const BigDecimalInt &num) const {
    if(this->getSign() != num.getSign())
    {
        BigDecimalInt temp(num);
        temp.setSign(this-> getSign());
        return *this+temp;
    }
    // "124"
    // "012"
    BigDecimalInt result;
    result.digits.clear();
    // BigDecimalInt bigger = max(*this, num);
    // BigDecimalInt smaller = min(*this, num);
    if(this->getSize() > num.getSize() || ( this->getSize() == num.getSize() && (*this > num  || *this == num) ) )
    {
        // leading zeros to make their size equal 
        BigDecimalInt num2;
        num2.digits.clear();
        for (int i = 0; i < this->getSize() - num.getSize(); i++){
            num2.digits.push_back('0');
        }
        for (char i : num.digits)
            num2.digits.push_back(i);

        // copy num 1
        BigDecimalInt num1 = *this;

        // sub
        for (int i =  num2.getSize() - 1 ; i >= 0; i--) {
            if(num1.digits[i] < num2.digits[i]) {
                num1.digits[i-1]--;
                num1.digits[i] += 10;
                result.digits.push_front('0' + num1.digits[i] - num2.digits[i]);
            }
            else {
                result.digits.push_front('0' + num1.digits[i] - num2.digits[i]);
            }
        }
    }
    else
    {
        // ***************** bug ******************
        // cout << "-";
        result.setSign('-');
        return num - *this;
    }
    return result;
}