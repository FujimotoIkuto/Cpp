#include <iostream>
using namespace std;

int main(){
    int a[10];

    a[0]=100;
    a[1]=200;
    a[5]=a[0]+a[1];
    //a[10]=200; //これはできない←a[10]はa[0]~a[9]

    cout << "a[0]=" << a[0] << '\n';
    cout << "a[1]=" << a[1] << '\n';
    cout << "a[5]=" << a[5] << '\n';

    return 0;
}