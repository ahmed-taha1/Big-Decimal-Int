

#include "BigDecimalInt.h"
using namespace std;

BigDecimalInt::BigDecimalInt(const string& num) {
    bool valid= true;
    if(num[0] != '+' && num[0] != '-' && !isdigit(num[0]))
    {
        valid = false;
    }
    else
    {
        bool leadingZero = true;
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
    if(!valid)
    {
        digits.push_back('0');
        setSign('0');
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
        setSign('0');
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



void BigDecimalInt::setSign(char num) {
    if(!isdigit(num))
    {
        sign = num;
    }
    else if(num!='0')
    {
        sign = '+';
    }
    else
    {
        sign = '0';
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

BigDecimalInt BigDecimalInt::operator+(const BigDecimalInt &num) {

    int carry = 0 ;
    int leftIdx = this->getSize() - 1;
    int rightIdx = num.getSize() - 1;

    BigDecimalInt result;
    result.digits.clear();
    if(this->getSign() == num.getSign())
    {
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
        result.setSign(result.digits[0]);
    }
    else
    {
        //return *this-num;
    }
    return  result;
}

ostream& operator<<(ostream& out,const BigDecimalInt& bigint) {
    if(bigint.getSign()=='-')
        out<<'-';

    for (int i = 0; i <bigint.getSize(); ++i) {
        out<<bigint.digits[i];
    }
    return out;
}

