//
// Created by ADHAM on 10/5/2022.
//

#ifndef ASS1_BIGDECIMALINT_H
#define ASS1_BIGDECIMALINT_H
#include<bits/stdc++.h>
using namespace std;

class BigDecimalInt {

private:
    deque<char> number;
    long long size;
    char sign;

public:
    BigDecimalInt(const string& num);
    BigDecimalInt(const int& num=0);




};


#endif //ASS1_BIGDECIMALINT_H
