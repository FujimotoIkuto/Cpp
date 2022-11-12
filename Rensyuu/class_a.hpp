#ifndef CLASS_A_HPP
#define CLASS_A_HPP

#include <iostream>

class A
{
    private:
        std::string _a_string;
    public:
        void intitialize(std::string a_string);
        void print();
};

void A::intitialize(std::string a_string)
{
    _a_string = a_string;
}

void A::print()
{
    std::cout << _a_string << std::endl;
}

#endif