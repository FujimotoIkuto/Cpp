#include "class_led.hpp"
#include "Arduino.h"

Led led;

void setup()
{
    led.setPinNumber(13);
}

void loop()
{
    led.turnOn();
    delay(1000);
    led.turnOff();
    delay(1000);
}
