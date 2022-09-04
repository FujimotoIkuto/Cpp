#include <iostream>
#include <string>
using namespace std;

// クラスの定義
class Person{
private:
    string name;
    int age;
public:
    Person();
    Person(string s);
    Person(int i);
    Person(string s, int i);
    void setname(string s);
    void setage(int i);
    void disp();
};

// コンストラクタ(引数なし、名前だけ、年齢だけ、両方)
Person::Person(){
    name = "";
    age = 0;
}
Person::Person(string s){
    name = s;
    age = 0;
}
Person::Person(int i){
    name = "";
    age = i;
}
Person::Person(string s, int i){ // コンストラクタ(初期化用メンバ関数)は名前がクラス名と同じ、戻り値なし(voidでもない型なし)
    name = s;
    if (i > 0){
        age = i;
    }else{
        age = 0;
    }
}

// メンバ関数
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

// メイン関数
int main(){
    Person dt1; //dt1()で宣言するとうまく行かなかった引数ないのにカッコつけるのはだめなのか?

    Person dt2("鈴木二郎");
    Person dt3(33);
    Person dt4("鈴木四郎", 44);

    dt1.disp();
    dt2.disp();
    dt3.disp();
    dt4.disp();

    return 0;
}