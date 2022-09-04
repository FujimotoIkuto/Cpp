#include <iostream>
using namespace std;

void strout1(const char aa[]);
void strout2(const char *p);

int main(){
    char aa[]="abcde";

    strout1(aa);
    strout2(aa);
    strout1("こんにちは");
    strout2("こんにちは");

    return 0;
}

// 仮引数をconstにすることによって実引数を変更できないから安全
// むしろconstにしないと警告が出る(実行はできる)
// 文字列だから?ポインタだから?
void strout1(const char aa[]){
    cout << aa << endl;
}

void strout2(const char *p){
    cout << p << endl;
}