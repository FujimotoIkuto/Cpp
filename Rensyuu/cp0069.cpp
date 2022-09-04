#include <iostream>
using namespace std;

void ptr_fnc(int *p);
void san_fnc(int &r);

int main(){
    int a = 1111;

    ptr_fnc(&a); // ポインタなら引数に&をつける必要がある
    cout << "a=" << a << endl;

    a = 1111;

    san_fnc(a); // 参照なら変数そのままで引数にできる
    cout << "a=" << a << endl;


    return 0;
}

void ptr_fnc(int *p){
    *p *= 2; // 変数の中身を変えるときは*をつける必要がある
}

void san_fnc(int &r){ // 宣言のときは&をつけて変数名をそのまま代入
    r *= 2; // 変数の中身を変えたりするときは&とかはいらない アドレスの代入は1回きりだから区別が必要ない
}