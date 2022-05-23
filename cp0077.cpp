#include <iostream>
#include <string>
using namespace std;

class Person{
private:
    string name;
    int age;
public:
    Person(string s, int i);
    void setname(string s);
    void setage(int i);
    void disp();
};

Person::Person(string s, int i){ // コンストラクタ(初期化用メンバ関数)は名前がクラス名と同じ、戻り値なし(voidでもない型なし)
    name = s;
    if (i > 0){
        age = i;
    }else{
        age = 0;
    }
}
void Person::setname(string s){
    name = s;
}
void Person::setage(int i){
    if (i > 0){
        age = i;
    }else{
        age = 0;
    }
}
void Person::disp(){
    cout << "名前= " << name << " 年齢= " << age << endl;
}

int main(){
    Person dt("鈴木五郎", 55);

    dt.disp();

    return 0;
}