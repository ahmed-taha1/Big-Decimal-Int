#include <bits/stdc++.h>
using namespace std;


class BigDecimalInt {
    private:
    string num;

    public:
    BigDecimalInt (string temp_num);
    friend::ostream & operator<<(ostream &os, BigDecimalInt& rec);
};

