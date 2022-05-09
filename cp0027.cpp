#include <iostream>
using namespace std;

int main(){
    int t, sum = 0;

    while(2){
        cout << "数値入力:";
        cin >> t;

        if (t == 0) break;

        sum += t;
    }
    cout << "数値の総和=" << sum << endl;

    return 0;
}
