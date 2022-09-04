#include "function_wait.hpp"
#include "Arduino.h"

void Wait::wait(unsigned int milliseconds)
{
    _start = millis();
    do{
        _end = millis();
    }while(_end-_start < milliseconds);

    return;
}

bool Wait::isWaiting(unsigned int milliseconds)
{
    if(_is_first)
    {
        _start = millis();
        _is_first = false;
    }

    _end = millis();

    if(_end-_start < milliseconds)
    {
        _end = millis();
        return true;
    }

    _is_first = true;
    return false;
}