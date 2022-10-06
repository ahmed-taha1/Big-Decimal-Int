#include <bits/stdc++.h>
#include "BigDecimalInt.cpp"
using namespace std;

int main(){
    system("CLS");
    string s1;   cin >> s1;
    BigDecimalInt h1(s1);

    string s2;  cin >> s2;
    BigDecimalInt h2(s2);
    cout << h2 << " " << h2.getSign() << " " << h2.getSize() << '\n';
    cout << h1 << " " << h1.getSign() << " " << h1.getSize() << '\n';

    BigDecimalInt h3 = h1 - h2;
    cout << h3.getSign();
    cout << BigDecimalInt(h1-h2);
}

// -123456789012345678901234567890
// -113456789011345678901134567890