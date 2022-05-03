#include <iostream>
#include <string> //string型用
#include <cstring> //strcpy用
using namespace std;

int main(){
    string s1, s2, s3;
    string ss;
    char cc[80];

    s1="abcd";
    s2="efgh";
    s3=s1+s2;

    cout << "s1=" << s1 << '\n';
    cout << "s2=" << s2 << '\n';
    cout << "s3=" << s3 << '\n';

    if (s1 == s2)
        cout << "s1とs2は等しい\n";
    else
        cout << "s1とs2は等しくない\n";
    
    strcpy(cc, "cccccc"); //char配列に文字列設定
    //文字列の代入: strcpy(ss, "abcde");
    //文字列の連結: strcat(ss, "12345");
    //文字列の比較: if (strcmp(ss, "12345") == 0) //差がゼロだったら的な


    ss=cc; //string型にchar配列を代入
    cout << "ss=" << ss << ", cc=" << cc << '\n';

    ss="ssssss"; //string型に文字列設定
    strcpy(cc, ss.c_str()); //char配列にstring型を代入  c_str()はメンバ関数というものらしい(よくわからん)
    cout << "ss=" << ss << ", cc=" << cc << '\n';

    return 0;
}