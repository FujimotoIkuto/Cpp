#include <iostream>
#include <string>
using namespace std;

// テンプレート関数記述。仮の型の名前をTとした
template <typename T> void maxa(T a, T b); // 関数名maxはエラーが出たからmaxaにした

int main(){
    int a=3, b=6;
    maxa(a,b);
    string c="abcd", d="efgh";
    maxa(c,d);
    double  e=2.72, f=3.14;
    maxa(e,f);

    return 0; 
}

template <typename T> void maxa(T a, T b){
    if (a > b){
        cout << a << endl;
    }else{
        cout << b << endl;
    }
}