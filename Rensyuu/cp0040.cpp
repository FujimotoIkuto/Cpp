#include <iostream>
using namespace std;

int main(){
    double dt, sum = 0;

    while(cin >> dt) {
        sum += dt;
    }

    cout << sum << endl;

    return 0;
}