#include <iostream>
#include "class_hello.hpp"

void Hello::setTimes()
{
    std::cout << "回数を入力してください" << std::endl;
    std::cin >> _times;
}

void Hello::printHello()
{
    for(int i=0; i<_times; i++){
        std::cout << "Hello, World!!" << std::endl;
    }
}