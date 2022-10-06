//#include <bits/stdc++.h>
#include <regex>
#include "BigDecimalInt.h"
using namespace std;


// ******************************** String Constructor ****************************


BigDecimalInt::BigDecimalInt(const string& num) {
    // validating (leading zeros ,sign ,etc....)
    validate(num);
}



// ***************************** Copy Constructor ***************************************
BigDecimalInt::BigDecimalInt(const BigDecimalInt &other) {

    // extracting  digits
    string num ;
    for (int i = 0; i <other.getSize(); ++i) {
        num+=other.digits[i];
    }

    // validating (leading zeros ,sign ,etc....)
    validate(num);
    setSign(other.getSign());
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


// ******************************* Assign Operator Function *****************************


BigDecimalInt& BigDecimalInt::operator=(const BigDecimalInt &num) {
    this->digits.clear();
    this->setSign(num.getSign());
    for (int i = 0; i <num.getSize(); ++i) {
        digits.push_back(num.digits[i]);
    }
    return *this;
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



// ******************************** Addition Function ****************************


BigDecimalInt BigDecimalInt::operator+(const BigDecimalInt &num)const {
    if(this->getSign() != num.getSign())
    {
        return *this-num;
    }

    BigDecimalInt result;
    result.digits.clear();
    result.setSign(this->getSign());

    BigDecimalInt lhs = *this;
    BigDecimalInt rhs = num;

    // equate the sizes of the two numbers
    int diff = abs(lhs.getSize()-rhs.getSize());
    for (int i = 0; i <diff; ++i) {
        if(rhs.getSize()<lhs.getSize())
            rhs.digits.push_front('0');
        else
            lhs.digits.push_front('0');
    }

    int end = lhs.getSize()-1;
    int carry = 0 ;

    while (end>=0)
    {
        int d1 =  lhs.digits[end] - '0';
        int d2 =  rhs.digits[end] - '0';
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
        end--;
    }
    if(carry)
    {
        result.digits.push_front(carry + '0');
    }
    return  result;
}



// ***************************** Subtraction Function *******************************


BigDecimalInt BigDecimalInt::operator-(const BigDecimalInt &num)const{
    // call sum operator
    if(this->getSign() != num.getSign())
    {
        BigDecimalInt temp(num);
        temp.setSign(this-> getSign());
        return *this+temp;
    }

    BigDecimalInt result,bigger,smaller,lhs,rhs;
    result.digits.clear();

    lhs = *this;
    char lhsSign = lhs.getSign();// save old sign
    lhs.setSign('+'); // get abs value

    rhs = num;
    if(rhs.getSign()=='+') // flip sign
        rhs.setSign('-');
    else
        rhs.setSign('+');

    char rhsSign = rhs.getSign();// save old sign
    rhs.setSign('+');// get abs value

    if(lhs>rhs)
    {
        result.setSign(lhsSign);
        bigger = lhs;
        smaller = rhs;
    }
    else if(rhs>lhs)
    {
        result.setSign(rhsSign);
        bigger = rhs;
        smaller = lhs;
    }
    else
    {
        result.setSign('+');
        return BigDecimalInt("0");
    }

     // equate the sizes of the two numbers
    int diff = abs(bigger.getSize()-smaller.getSize());
    for (int i = 0; i <diff; ++i) {
        if(smaller.getSize()<bigger.getSize())
              smaller.digits.push_front('0');
        else
            bigger.digits.push_front('0');
    }

    // subtraction
    for (int i =  bigger.getSize()-1 ; i >= 0; i--) {
        if(bigger.digits[i] < smaller.digits[i]) {
            bigger.digits[i-1]--;
            bigger.digits[i] += 10;
            result.digits.push_front('0' + bigger.digits[i] - smaller.digits[i]);
        }
        else {
            result.digits.push_front('0' + bigger.digits[i] - smaller.digits[i]);
        }

    }
     return result;
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

// ****************************** Output Operator Overloading Function ******************************


ostream& operator<<(ostream& out,const BigDecimalInt& bigint) {
    if(bigint.getSign()=='-')
        out<<'-';

    for (int i = 0; i <bigint.getSize(); ++i) {
        out<<bigint.digits[i];
    }
    return out;
}

// ****************************** Validating number **************************************************

void BigDecimalInt::validate(const string &num){
    bool valid = true;
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

// ********************************************************************************************
