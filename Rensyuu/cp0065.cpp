#include <iostream>
using namespace std;

int main(){
    char ss[] = "ABCDE";
    char *p;

    p = ss; // 配列名はそのままでアドレスになる

    cout << "(1)ssとpと*pを使って表示する\n";
    cout << "   ss=" << ss << " p=" << p << " *p=" << *p << endl;

    cout << "(2)p+1とp+2を使って表示する\n";
    cout << "   p+1=" << p+1 << " p+2=" << p+2 << endl;

    cout << "(3)++p後のpを表示する\n";
    ++p;
    cout << "   p=" << p << endl;

    cout << "(4)現在のp位置とss[2]の内容を更新する\n";
    *p = 'x';
    ss[2] = 'y';
    cout << "   ss=" << ss << endl;

    return 0;
}