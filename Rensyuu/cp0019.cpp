#include <iostream>
using namespace std;

int main()
{
    int n;
    cout << "数値=";
    cin >> n;

    switch(n){ //ここでswitch(int n)とか宣言してもいい　読み取りは中でガンバ
        case 1:
            cout << "数値は1です。\n";
            break;
        case 3:
            cout << "数値は3です。\n";
            break;
        case 5:
            cout << "数値は5です。\n";
            break;
        default:
            cout <<  "数値は1,3,5以外です。\n";
            break;
    }

    return 0;
}