#include <iostream>
using namespace std;

int main()
{
    cout  << "bool  = " << sizeof(bool) << '\n';
    cout  << "char  = " << sizeof(char) << '\n';
    cout  << "int   = " << sizeof(int) << '\n';
    cout  << "long= " << sizeof(long) << '\n'; //longはlong intのことだと思う
    cout  << "float = " << sizeof(float) << '\n';
    cout  << "double= " << sizeof(double) << '\n';
    cout  << "long double= " << sizeof(long double) << '\n';

    return 0;
}