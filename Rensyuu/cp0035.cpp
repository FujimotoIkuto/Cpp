#include <iostream>
#include <cctype> //toupper用
using namespace std;

int main(){
    char ch;

    while (cin.get(ch)){ //入力終了になるまでループする
        ch = toupper(ch); //大文字にする
        cout.put(ch);
    }
    //入力終了は[Ctrl]+[D]キー

    return 0;
}