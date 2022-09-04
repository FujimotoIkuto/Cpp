#include <iostream>
#include <string>
using namespace std;

template <typename T1, typename T2> void disp(string ss, T1 a, T2 b);

int main(){
    disp("test1", 12345, 66.77);
    disp("test2", 88.99, "ABCDE");

    return 0;
}

template <typename T1, typename T2> void disp(string ss, T1 a, T2 b){
    cout << ss << ':' << a << ',' << b << endl;
}