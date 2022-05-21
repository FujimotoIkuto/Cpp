#include <iostream>
using namespace std;

void change(int *p);

int main(){
    int a = 1234;
    cout << "a=" << a << endl;
    change(&a);
    cout << "a=" << a << endl;
}

void change(int *p){
    *p *= 2;
}