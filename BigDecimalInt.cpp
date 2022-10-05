//
// Created by ADHAM on 10/5/2022.
//

#include "BigDecimalInt.h"

BigDecimalInt::BigDecimalInt(const string& num) {
    bool valid= true;
    if(num[0] != '+' ||num[0] != '-' || !isdigit(num[0]))
    {
        valid= false;

    }
    else
    {
        bool leadingZero=true;
        if(isdigit(num[0]) && num[0] != '0')
        {
            number.push_back(num[0]);
            leadingZero= false;
        }

        for (int i = 1; i <num.size() ; ++i) {
            if(num[i]=='0' && leadingZero)
            {
                continue;
            }
            if(!isdigit(num[i]))
            {
               valid= false;
                break;
            }

            leadingZero=false;
            number.push_back(num[i]);

        }

    }
    if(!valid)
    {
        number.push_back('0');
    }


}

BigDecimalInt::BigDecimalInt(const int & num) {
    int temp=num;
    if(num==0)
    {
        number.push_back('0');
    }
    else if(num<0)
    {
        sign='-';
        temp*=-1;

    }

    while(temp)
    {
        int digit=num%10;
        temp/=10;
        number.push_front(digit+'0');



    }



}
