#include <bits/stdc++.h>
using namespace std;


class BigDecimalInt {
    private:
    deque <char> num;

    public:
    BigDecimalInt (string temp_num);
    BigDecimalInt (int decInt);
    friend::ostream & operator<<(ostream &os, BigDecimalInt& temp_num);
    BigDecimalInt operator+ (BigDecimalInt anotherDec);
    bool operator< (BigDecimalInt anotherDec);
    bool operator> (BigDecimalInt anotherDec);
    bool operator==(BigDecimalInt anotherDec);
    friend::ostream& operator << (ostream& out, BigDecimalInt b);
};

