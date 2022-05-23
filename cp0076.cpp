#include <iostream>
#include <string>
using namespace std;

class Person{
private:
    string name;
    int age;
public:
    void setname(string s);
    void setage(int i);
    void disp();
};

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
    Person dt;

    dt.setname("山田一郎");
    dt.setage(-10);
    dt.disp();

    return 0;
}