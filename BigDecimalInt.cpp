

#include "BigDecimalInt.h"
using namespace std;

BigDecimalInt::BigDecimalInt(const string& num) {
    bool valid= true;
    bool leadingZero = true;
    if(num[0] != '+' && num[0] != '-' && !isdigit(num[0]))
    {
        valid = false;
    }
    else
    {
        if(isdigit(num[0]) && num[0] != '0')
        {
            digits.push_back(num[0]);
            leadingZero = false;
        }
        for (int i = 1; i <num.size() ; ++i) {
            if(num[i] == '0' && leadingZero)
            {
                continue;
            }
            if(!isdigit(num[i]))
            {
                valid = false;
                break;
            }

            leadingZero = false;
            digits.push_back(num[i]);

        }
    }
    if(!valid||leadingZero)
    {
        digits.push_back('0');
        setSign('+');
    }
    else{
        setSign(num[0]);
    }
}

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

int BigDecimalInt::getSize() const {
    return  digits.size();
}

char BigDecimalInt::getSign() const {
    return  sign;
}



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

BigDecimalInt::BigDecimalInt(const BigDecimalInt &other) {
    *this = other;
}

BigDecimalInt& BigDecimalInt::operator=(const BigDecimalInt &num) {
    this->digits.clear();
    for (int i = 0; i <num.getSize(); ++i) {
        digits.push_back(num.digits[i]);
    }
    return *this;
}

BigDecimalInt BigDecimalInt::operator+(const BigDecimalInt &num)const {
    if(this->getSign() != num.getSign())
    {
        //return *this-num;
        cout<<"MINUS\n";
        exit(0);
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


BigDecimalInt BigDecimalInt::operator-(const BigDecimalInt &num) const {
    if(this->getSign() != num.getSign())
    {
        BigDecimalInt temp(num);
        temp.setSign(this->getSign());
        return *this+temp;
    }

}


ostream& operator<<(ostream& out,const BigDecimalInt& bigint) {
    if(bigint.getSign()=='-')
        out<<'-';

    for (int i = 0; i <bigint.getSize(); ++i) {
        out<<bigint.digits[i];
    }
    return out;
}

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

bool BigDecimalInt::operator==(const BigDecimalInt& anotherDec)const{
    return (!(*this < anotherDec) && !(*this > anotherDec));
}

