#ifndef CLASS_B_HPP
#define CLASS_B_HPP

#include "class_a.hpp"
#include <iostream>

class B
{
    private:
        A _a;
    public:
        B();
        void initialize();
        void print();
};

B::B()
{
    initialize();
}

void B::initialize()
{
    _a.intitialize("This is A");
}

void B::print()
{
    _a.print();
}

#endif