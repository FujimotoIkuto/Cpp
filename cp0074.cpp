#include <iostream>
using namespace std;

enum Color {RED, BLUE, GREEN=5, YELLOW}; // 列挙体のcolorを宣言
// 列挙体はfalse=0,true=その他、のように数字に名前をつけることができる
// この場合はRED=0,BLUE=1,GREEN=5,YELLOW=6

int main(){
    Color dt;
    int n;

    dt = BLUE;
    if (dt == RED){
        cout << "dtはREDです。\n";
    }else if (dt == BLUE){
        cout << "dtはBLUEです。\n";
    }else if (dt == GREEN){
        cout << "dtはGREENです。\n";
    }else if (dt == YELLOW){
        cout << "dtはYELLOWです。\n";
    }

    n = GREEN;
    cout << "nは " << n << " です。\n";
    
    cout << "REDは " << RED << "YELLOWは " << YELLOW << "です。\n";

    return 0;
}