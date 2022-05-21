#include <iostream>
using namespace std;

int main(){
    int a = 123, b;
    int *p; // int* p; でも良い

    p = &a; // 変数aのアドレスをpに入れる
    b = *p; // ポインタpの示すアドレスにある値をbに入れる

    // ポインタでアドレスをやり取りするときは'p'でポインタで値をやり取りするときは"*p"のように見える

    cout << "a=" << a << " *p=" << *p << " b=" << b << '\n';

    return 0;
}