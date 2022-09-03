#include "class_hello.hpp"
#include <iostream>

// Compile "$ g++ -o main_hello main_hello.cpp class_hello.cpp"

// class Hello
// {
//     private:
//         int _times;
    
//     public:
//         void setTimes();
//         void printHello();
// };

int main()
{
    Hello hello;
    hello.setTimes();
    hello.printHello();

    return 0;
}

// void Hello::setTimes()
// {
//     std::cout << "回数を入力してください" << std::endl;
//     std::cin >> _times;
// }

// void Hello::printHello()
// {
//     for(int i=0; i<_times; i++){
//         std::cout << "Hello, World!!" << std::endl;
//     }
// }