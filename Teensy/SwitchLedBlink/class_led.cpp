#include "class_led.hpp"
#include "Arduino.h"

void Led::setPinNumber(int pin_number)
{
    _pin_number = pin_number;
    pinMode(_pin_number, OUTPUT);
}

void Led::turnOn()
{
    digitalWrite(_pin_number, HIGH);
}

void Led::turnOff()
{
    digitalWrite(_pin_number, LOW);
}