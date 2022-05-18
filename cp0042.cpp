#include <iostream>
#include <string>
#include <cstdlib> //atoi用
using namespace std;

int main(){
    string ss;
    int dt = 1234;

    cout << "数値1を入力してください\n";
    cin >> ss;
    dt = atoi(ss.c_str()); //文字列を適する数値型に変換する0にする(intでもdoubleとかでもいい)
    cout << "数値1は" << dt << "です\n";

    cout << "数値2を入力してください\n";
    cin >> ss;
    dt = atoi(ss.c_str());
    cout << "数値2は" << dt << "です\n";

    cout << "数値3を入力してください\n";
    cin >> ss;
    dt = atoi(ss.c_str());
    cout << "数値3は" << dt << "です\n";

    return 0;
}