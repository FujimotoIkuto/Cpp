#include <iostream>

int main(){
    int a,t,n,z;

    a = '\a';
    t = '\t';
    n = '\n';
    z = '\0';

    std::cout << "a:" << a << '\n';
    std::cout << "t:" << t << '\n';
    std::cout << "n:" << n << '\n';
    std::cout << "z:" << z << '\n';

    std::cout << "\a警告音\n";
    std::cout << "AAA\tBBB\tCCC\nDDD\tEEE\tFFF\n";

    return 0;
}