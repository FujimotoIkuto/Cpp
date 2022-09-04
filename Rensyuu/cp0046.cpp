#include <iostream>
using namespace std;

double average(double x, double y); // 関数averageのプロトタイプ宣言

int main(){
    double a, b;

    cout << "数字1を入力してください\n";
    cin >> a;
    cout << "数字2を入力してください\n";
    cin >> b;

    double c = average(a, b);
    cout << "数字1と数字2の平均値は" << c << "です\n";

    return 0;
}

double average(double x, double y){
    double z = (x+y)/2;
    return z;
}