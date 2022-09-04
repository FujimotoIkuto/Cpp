#include <iostream>
using namespace std;

int main()
{
    int i8, i10, i16;
    double ff, fe;

    i8=0123;
    i10=123;
    i16=0x123;
    ff=12.345;
    fe=3.456e2;

    cout << " 8進123 =" << i8 << '\n';
    cout << "10進123 =" << i10 << '\n';
    cout << "16進123 =" << i16 << '\n';
    cout << "小数点  =" << ff << '\n';
    cout << "指数    =" << fe << '\n';

    return 0;
}