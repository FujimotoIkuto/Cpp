#include <iostream>
using namespace std;

void disp(int a, int b=200, int c=300); // デフォルト引数の後ろに未設定引数は書けない 例:a(デフォルト)b(未指定)c(デフォルト)とはできない

int main(){
    disp(111);
    disp(111, 222);
    disp(111, 222, 333);
    //disp(); // aはデフォルトを設定していないので必要

    return 0;
}

void disp(int a, int b, int c){
    cout << "a=" << a << "b=" << b << "c=" << c << endl;
}