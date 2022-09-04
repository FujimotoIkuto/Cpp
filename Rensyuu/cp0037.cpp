#include <iostream>
#include <string>
using namespace std;

int main(){
    string s;

    cout << "文字列を入力:";
    getline(cin, s); //行単位で読み取るから間に空白(スペース)があっても大丈夫   cin.get(s) (←→cout.put(s))の文字列版
    cout << s << endl;
    //cout << s[2] << endl; //stringも順番に配列に入っている

    return 0;
}